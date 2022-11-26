# add_subdirectory(third)
add_subdirectory(other)

add_executable(main main.cpp)
add_executable(temp temp.cpp)
add_executable(hhh hhh.cpp)

target_link_libraries(
    temp
    -lpthread
)
