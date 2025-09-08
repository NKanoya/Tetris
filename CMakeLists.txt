cmake_minimum_required(VERSION 3.29)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/block_matrix)
add_subdirectory(src/rotate)
add_subdirectory(src/wall_kick)
add_subdirectory(src/tetromino)
add_subdirectory(src/matrix_state_manager)

# test instance
# add_subdirectory(test/test_block_matrix)
# add_subdirectory(test/test_rotate)
add_subdirectory(test/test_adjacent_states)

add_executable(
        Tetris
        main.cpp
)


target_link_libraries(Tetris
        PRIVATE block_matrix
        PRIVATE tetromino
        PRIVATE rotate
        PRIVATE wall_kick
        PRIVATE matrix_state_manager

        # test instance
        # PRIVATE test_block_matrix
        # PRIVATE test_rotate
        PRIVATE test_adjacent_states
)
