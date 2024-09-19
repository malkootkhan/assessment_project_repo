cmake_minimum_required(VERSION 3.22)
project(queueExec)

# Download and build GoogleTest only if necessary
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

#set debug flag
set(CMAKE_BUILD_TYPE debug)

# Add the test executable
add_executable(test_queue test_queue.cpp)

# Link GoogleTest and the main project library
target_link_libraries(test_queue gtest gtest_main)
# Add the test to CTest
enable_testing()
add_test(NAME test_queue COMMAND test_queue)

