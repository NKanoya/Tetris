cmake_minimum_required(VERSION 3.29)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/block_map)

# test instance
add_subdirectory(test/test_block_map)

add_executable(
        Tetris
        main.cpp
        temp/tetromino/tetromino.cpp
        temp/tetromino.hpp
)


target_link_libraries(Tetris
        PRIVATE block_map
        #test instance
        PRIVATE test_block_map
)
