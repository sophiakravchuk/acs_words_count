cmake_minimum_required(VERSION 3.15)
project(word_c2)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
add_executable(word_c2 main.cpp)
#add_executable(word_c2_q main.cpp queue.cpp)

target_link_libraries(word_c2 Threads::Threads)
