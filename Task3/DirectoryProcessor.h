#pragma once

#include <string>
#include <deque>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>

enum ProcessFlagBits
{
	SAVE_GENERAL_STATS = 1,
	SAVE_INDIVIDUAL_FILES_STATS = 2,
	SEPARATE_COMMENTS_AND_CODE = 4,
	DEFAULT = SAVE_GENERAL_STATS | SAVE_INDIVIDUAL_FILES_STATS
};
typedef uint8_t ProcessFlags;

class DirectoryProcessor
{
public:

	struct CodeStats
	{
		std::string file_name;
		uint32_t blank_lines = 0;
		uint32_t comment_lines = 0;
		uint32_t code_lines = 0;

		CodeStats& operator+=(const CodeStats& other);
	};

public:
	DirectoryProcessor();
	DirectoryProcessor(int threads_count);
	~DirectoryProcessor() = default;

	virtual void ProcessDirectory(const std::string& root_path, ProcessFlags flags = DEFAULT);
	
	void WriteStats(const std::string& file_path);

	void set_threads_count(int threads_count);
	int get_threads_count() const { return m_threads_count; }

	CodeStats get_general_stats();
protected:
	bool CheckExtensions(const std::string& extension);

	virtual void ProcessFile();
	virtual void EnqueValidFiles(const std::string& root_path);

protected:

	std::deque<CodeStats> m_code_stats;
	std::queue<std::string> m_files_queue;
	std::vector<std::thread> m_threads;
	int m_threads_count;

	std::condition_variable m_cv;
	std::mutex m_queue_mutex;
	std::mutex m_stats_mutex;

	CodeStats m_general_code_stats;
	uint32_t m_files_processed = 0;
	uint32_t m_total_files = 0;
	std::chrono::duration<double> m_process_time;

	ProcessFlags m_flags = 0;
	bool m_isProccesed = false;
};

