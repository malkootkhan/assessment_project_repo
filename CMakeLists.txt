cmake_minimum_required(VERSION 3.22)
project(BOSCH_assessment)

#C++ std 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(include)

#specify the output executable path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

