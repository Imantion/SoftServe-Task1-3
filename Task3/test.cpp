#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <limits>
#include "DirectoryProcessor.h"

class DirectoryProcessorTest : public ::testing::Test {
protected:
    DirectoryProcessorTest() {
    }

    ~DirectoryProcessorTest() override {
    }

    DirectoryProcessor dp; 
};

TEST_F(DirectoryProcessorTest, ConstructorWithInvalidThreadCountThrows) {

    EXPECT_THROW(DirectoryProcessor(-1), std::invalid_argument);
    EXPECT_THROW(DirectoryProcessor(0), std::invalid_argument);
    EXPECT_THROW(DirectoryProcessor(std::numeric_limits<uint64_t>().max()), std::invalid_argument);
}

TEST_F(DirectoryProcessorTest, ProcessDirectoryWithNoFlagsThrows) {

    EXPECT_THROW(dp.ProcessDirectory("some/directory", 0), std::invalid_argument);
}


TEST_F(DirectoryProcessorTest, GetGeneralStatsWithNoProcessedDirectoryThrows) {
    EXPECT_THROW(dp.get_general_stats(), std::runtime_error);
}

TEST_F(DirectoryProcessorTest, WriteStatsWithNoProcessedDirectoryThrows) {
    EXPECT_THROW(dp.WriteStats("some/file.txt"), std::runtime_error);
}

class MockDirectoryProcessor : public DirectoryProcessor
{
public:
    MockDirectoryProcessor() = default;
	~MockDirectoryProcessor() = default;

    MOCK_METHOD(void, ProcessFile, (), (override));
	MOCK_METHOD(void, EnqueValidFiles, (const std::string& root_path), (override));
    
};

class MockDirectoryProcessorParamTest : public ::testing::TestWithParam<int> {
public:
protected:
	MockDirectoryProcessor mdp;
};

TEST_P(MockDirectoryProcessorParamTest, ProcessFileTest) {
   
	int threads_count = GetParam();

	try
	{
		mdp.set_threads_count(threads_count);
	}
	catch (const std::exception&)
	{
		threads_count = mdp.get_threads_count();
	}
	
	EXPECT_CALL(mdp, ProcessFile()).Times(threads_count);
	EXPECT_CALL(mdp, EnqueValidFiles(testing::_)).Times(1);

	mdp.ProcessDirectory("some/directory", SAVE_GENERAL_STATS | SAVE_INDIVIDUAL_FILES_STATS);
}

INSTANTIATE_TEST_CASE_P(ThreadsCount, MockDirectoryProcessorParamTest, testing::Values(1, 4, 6, 8, 10));