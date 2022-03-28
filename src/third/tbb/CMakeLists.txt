add_executable(third_tbb_test test.cpp)

target_link_libraries(
        third_tbb_test
        -ltbb
)