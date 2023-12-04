cmake_minimum_required(VERSION 3.12)
project(QuickSortTest)

# Set C++20 as the standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable for the test_sorting.cpp file.
add_executable(QuickSortTest tests/test_sorting.cpp)

# Include the directory where quick_sort.hpp is located.
target_include_directories(QuickSortTest PRIVATE ${PROJECT_SOURCE_DIR})
