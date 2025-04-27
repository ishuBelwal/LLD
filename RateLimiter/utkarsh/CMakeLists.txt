
cmake_minimum_required(VERSION 3.10)
project(RateLimiterTest)

# Enable C++17 or higher
set(CMAKE_CXX_STANDARD 17)

# Add source files
add_executable(main
    main.cpp
    fixedWindow.cpp
)

# Link Google Test (assuming it's installed system-wide)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(main
    ${GTEST_LIBRARIES}
    pthread  # Required by Google Test
)
