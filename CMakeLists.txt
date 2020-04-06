cmake_minimum_required(VERSION 3.15)
project(word_c2)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
find_package(libzipstatic REQUIRED)
file (GLOB SOURCES
        main.cpp

        queue.cpp
        queue.h
        threads_merge.cpp
        threads_merge.h
        time_measurement.cpp
        time_measurement.h
        file_of_vecs.h
        file_to_vecs.cpp
)

add_executable(word_c2 ${SOURCES})
#add_executable(word_c2_q main.cpp queue.cpp)

target_link_libraries(word_c2 Threads::Threads)
target_link_libraries(word_c2 libzipstatic)
