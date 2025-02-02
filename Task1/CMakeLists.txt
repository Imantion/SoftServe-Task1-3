# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# Set the project name
project(StringListExample)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)  # Use C++11, change if needed (e.g., 17, 20, etc.)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

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
    StringList.cpp # Implementation file for StringList
)

add_executable(testRunner
    test.cpp       # The main program
    StringList.cpp # Implementation file for StringList
)
target_link_libraries(testRunner gtest_main gmock_main)

# Include directories (not required here since .h files are in the same directory)
# If headers are in a subfolder, you can specify the path:
# target_include_directories(${PROJECT_NAME} PRIVATE include_directory)

# Optionally add compile options or definitions
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# Libraries like stdlib.h and string.h are part of the C++ standard library,
# so no need to link additional libraries explicitly for them.
