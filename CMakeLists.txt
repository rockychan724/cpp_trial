cmake_minimum_required(VERSION 3.15)

project(cpp_trial)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE src_list src/*.cpp)

include_directories(
        /usr/local/opencv4/include/opencv4
        /usr/include/python3.8
)

link_directories(
        /usr/local/opencv4/lib
)

add_executable(cpp_trial src/main.cpp)

#target_link_libraries(
#        cpp_trial
#        -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
#        -lpthread
#        -ltbb
#        -luuid
#)
