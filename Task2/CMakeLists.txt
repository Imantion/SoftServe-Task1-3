# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(VariantPrimitive)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)  # Use C++11, change if needed (e.g., 17, 20, etc.)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(${PROJECT_NAME}
    main.cpp       # The main program
    VariantPrimitive.cpp # Implementation file for StringList
)

# Include directories (not required here since .h files are in the same directory)
# If headers are in a subfolder, you can specify the path:
# target_include_directories(${PROJECT_NAME} PRIVATE include_directory)

# Optionally add compile options or definitions
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# Libraries like stdlib.h and string.h are part of the C++ standard library,
# so no need to link additional libraries explicitly for them.
