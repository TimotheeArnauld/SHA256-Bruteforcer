cmake_minimum_required(VERSION 3.0)
project(producer_consumer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(SOURCE_FILES src/sha256.cpp src/parseargs.cpp src/bruteforce.cpp src/main.cpp)
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${dir})

add_executable(bruteforcer ${SOURCE_FILES})

find_package(Threads)
target_link_libraries(bruteforcer ${CMAKE_THREAD_LIBS_INIT})
