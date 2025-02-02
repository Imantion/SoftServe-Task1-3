# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.17)

# Set the project name
project(DirectoryProcessor)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)  # Use C++11, change if needed (e.g., 17, 20, etc.)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#get googletest
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG       v1.15.2)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
    FetchContent_MakeAvailable(googletest)
endif()

# Add the executable target
add_executable(${PROJECT_NAME}
    main.cpp       # The main program
    DirectoryProcessor.cpp # Implementation file for StringList
)


add_executable(testRunner
    test.cpp       # The main program
    DirectoryProcessor.cpp # Implementation file for StringList
)
target_link_libraries(testRunner gtest_main gmock_main)