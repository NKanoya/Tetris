cmake_minimum_required(VERSION 3.29)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

# add_subdirectory(src/block_map)
add_subdirectory(src/rotate)
add_subdirectory(src/wall_kick)
# add_subdirectory(src/tetromino)

# test instance
# add_subdirectory(test/test_block_map)
add_subdirectory(test/test_rotate)

add_executable(
        Tetris
        main.cpp
)


target_link_libraries(Tetris
        # PRIVATE block_map
        # PRIVATE tetromino
        PRIVATE rotate
        PRIVATE wall_kick

        # test instance
        # PRIVATE test_block_map
        PRIVATE test_rotate
)
