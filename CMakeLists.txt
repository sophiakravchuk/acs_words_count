cmake_minimum_required(VERSION 3.15)
project(word_c2)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)

set(LibZip_LIBRARIES "")
include(CheckLibraryExists)
SET(LibZip_LIBRARY_PATH "")
check_library_exists(zip zip_open_from_source
        "${LibZip_LIBRARY_PATH}" LibZip_FOUND)
if(LibZip_FOUND)
    message("Found LibZip")
    list(APPEND LibZip_LIBRARIES "zip" )
    link_directories(${LibZip_LIBRARY_PATH})
endif()

file (GLOB SOURCES
        main.cpp

        lib
        queue.cpp
        queue.h
        time_measurement.cpp
        time_measurement.h
        file_of_vecs.h
        file_to_vecs.cpp
)

add_executable(word_c2 ${SOURCES})
#add_executable(word_c2_q main.cpp queue.cpp)

target_link_libraries(word_c2 Threads::Threads)
target_link_libraries(word_c2  ${LibZip_LIBRARIES})

