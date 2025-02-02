#include <gtest/gtest.h>
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

