cmake_minimum_required(VERSION 3.15)

project(cpp_trial)

add_subdirectory(src/third)
add_subdirectory(src/other)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#file(GLOB_RECURSE src_list src/*.cpp)

add_executable(main src/main.cpp)
add_executable(temp src/temp.cpp)
add_executable(hhh src/hhh.cpp)

target_link_libraries(
    temp
    -lpthread
)
