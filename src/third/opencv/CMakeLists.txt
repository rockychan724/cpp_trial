include_directories(
        /usr/local/opencv4/include/opencv4
)

link_directories(
        /usr/local/opencv4/lib
)

add_executable(third_opencv_test test.cpp)

target_link_libraries(
        third_opencv_test
        -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
)
