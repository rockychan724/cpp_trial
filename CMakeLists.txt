cmake_minimum_required(VERSION 3.15)

project(cpp_trial)

add_subdirectory(src/third)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE src_list src/*.cpp)

include_directories(
        /usr/local/opencv4/include/opencv4
        /usr/include/python3.8
)

link_directories(
        /usr/local/opencv4/lib
)

add_executable(main src/main.cpp)
add_executable(temp src/temp.cpp)

