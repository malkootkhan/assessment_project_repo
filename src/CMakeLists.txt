# Find Threads package
find_package(Threads REQUIRED)

#enable debug flag
set(CMAKE_BUILD_TYPE debug)

#create the final executable
add_executable(queueExec main.cpp)

# Link the Threads library to the executable
target_link_libraries(queueExec PRIVATE Threads::Threads)


