add_executable(third_linux_test test.cpp)

target_link_libraries(
        third_linux_test
        -luuid
)
