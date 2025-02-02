#include "DirectoryProcessor.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <stdexcept>

namespace fs = std::filesystem;

inline bool IsWhitespace(int character)
{
    if (character > 255 || character < 0)
        return false;

    return std::isspace(character);
}

DirectoryProcessor::DirectoryProcessor()
{
    set_threads_count(std::thread::hardware_concurrency() - 1);
}

DirectoryProcessor::DirectoryProcessor(int threads_count)
{
	set_threads_count(threads_count);
}

void DirectoryProcessor::ProcessDirectory(const std::string& root_path, ProcessFlags flags /*=DEFAULT*/)
{
    if (flags == 0)
    {
        throw std::invalid_argument("No flags were set.");
    }

    for (size_t i = 0; i < m_threads_count; i++)
    {
        m_threads.emplace_back(std::thread(&DirectoryProcessor::ProcessFile, this));
    }

    auto start = std::chrono::high_resolution_clock::now();
    m_general_code_stats.file_name = root_path;
    m_flags = flags;

	EnqueValidFiles(root_path);

    while (!m_files_queue.empty())
    {
        m_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    {
        std::lock_guard<std::mutex> lock(m_queue_mutex);
        m_isProccesed = true;
    }
    m_cv.notify_all();

    for (auto& thread : m_threads)
    {
        if(thread.joinable())
            thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    m_process_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
}

void DirectoryProcessor::ProcessFile()
{
    while(!m_isProccesed)
    { 
        std::string file_name;

        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            m_cv.wait(lock, [this] { return !m_files_queue.empty() || m_isProccesed; });

            if (m_isProccesed && m_files_queue.empty())
                return;

            file_name = std::move(m_files_queue.front());
            m_files_queue.pop();
        }

        std::ifstream file(file_name);
        if (!file.is_open())
        {
            throw std::ios_base::failure("Cannot open file: " + file_name);
        }

        CodeStats stats;
        stats.file_name = file_name;

        std::string line;
        bool inMultiLineComment = false;

        while (std::getline(file, line)) 
        {
            if (line.empty() || std::all_of(line.begin(), line.end(), IsWhitespace))
            {
                stats.blank_lines++;
            }
            else if (inMultiLineComment) 
            {
                stats.comment_lines++;
                if (line.rfind("*/") != std::string::npos)
                {
                    inMultiLineComment = false;
                }
            }
            else if (line.find("/*") != std::string::npos)
            {
                stats.comment_lines++;
                inMultiLineComment = line.rfind("/*") != std::string::npos;
            }
            else if (line.find("//") != std::string::npos)
            {
                stats.comment_lines++;
            }
            else 
            {
                stats.code_lines++;
            }
        }

        file.close();

        {
            std::lock_guard<std::mutex> lock(m_stats_mutex);

            if (m_flags & SAVE_GENERAL_STATS)
                m_general_code_stats += stats;

            if (m_flags & SAVE_INDIVIDUAL_FILES_STATS)
                m_code_stats.emplace_back(stats);

            ++m_files_processed;
        }
    }
}

void DirectoryProcessor::EnqueValidFiles(const std::string& root_path)
{
    for (const auto& entry : fs::recursive_directory_iterator(root_path))
    {
        if (!entry.is_regular_file())
            continue;

        std::string extension = entry.path().extension().string();

        if (CheckExtensions(extension))
        {
            {
                std::lock_guard<std::mutex> lock(m_queue_mutex);
                m_files_queue.push(std::move(entry.path().string()));
            }
            m_cv.notify_one();
        }
    }
}

DirectoryProcessor::CodeStats DirectoryProcessor::get_general_stats()
{
    if (m_flags == 0 || !m_isProccesed)
    {
        throw std::runtime_error("No directory was processed.");
    }

    if(!(m_flags & SAVE_GENERAL_STATS))
        throw std::runtime_error("SAVE_GENERAL_STATS flags was not set");

    return m_general_code_stats;
}

void DirectoryProcessor::WriteStats(const std::string& file_path)
{
    if (m_flags == 0 || !m_isProccesed)
    {
        throw std::runtime_error("No directory was processed.");
    }
    
    std::ofstream output(file_path, std::ios_base::out);

    if (!output.is_open())
    {
        throw std::ios_base::failure("Cannot write to file: " + file_path);
    }

    if (m_flags & SAVE_GENERAL_STATS)
    {
        output << "Directory: " << m_general_code_stats.file_name << "\n";
        output << "Total files processed: " << m_files_processed << "\n";
        output << "Total code lines: " << m_general_code_stats.code_lines << "\n";
        output << "Total comment lines: " << m_general_code_stats.comment_lines << "\n";
        output << "Total blank lines: " << m_general_code_stats.blank_lines << "\n";
        output << "Total time: " << m_process_time.count() << "s\n";
    }

    if (m_flags & SAVE_INDIVIDUAL_FILES_STATS)
    {
        for (const auto& stats : m_code_stats)
        {
            output << "\n";
            output << "File: " << stats.file_name << "\n";
            output << "Code lines: " << stats.code_lines << "\n";
            output << "Comment lines: " << stats.comment_lines << "\n";
            output << "Blank lines: " << stats.blank_lines << "\n";
        }
    }
}

void DirectoryProcessor::set_threads_count(int threads_count)
{
    if (threads_count <= 0 || threads_count > ((int)std::thread::hardware_concurrency() - 1))
    {
        m_threads_count = std::thread::hardware_concurrency() - 1;
        throw std::invalid_argument("Invalid threads count. Setting to default value: " + std::to_string(m_threads_count));
    }
    else
    {
        m_threads_count = threads_count;
    }

    m_threads.reserve(m_threads_count);
}

bool DirectoryProcessor::CheckExtensions(const std::string& extension)
{
    return extension == ".h" || extension == ".hpp" || extension == ".c" || extension == ".cpp";
}

DirectoryProcessor::CodeStats& DirectoryProcessor::CodeStats::operator+=(const CodeStats& other)
{
    blank_lines += other.blank_lines;
    comment_lines += other.comment_lines;
    code_lines += other.code_lines;
    return *this;
}
