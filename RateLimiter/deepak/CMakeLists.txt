cmake_minimum_required(VERSION 3.10)
project(RateLimiterTest)

# Enable C++17 or higher
set(CMAKE_CXX_STANDARD 17)

# Include FetchContent module
include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

# Add source files
add_executable(
    RateLimiterTest
    fixedwindow.cpp
)

# Link with Google Test
target_link_libraries(
    RateLimiterTest
    gtest
    gtest_main
    pthread
)
