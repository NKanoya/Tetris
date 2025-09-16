cmake_minimum_required(VERSION 3.29)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/matrix_state_manager)
add_subdirectory(src/block_matrix)
add_subdirectory(src/rotate)
add_subdirectory(src/wall_kick)
add_subdirectory(src/tetromino)
add_subdirectory(src/bit_mask)
add_subdirectory(src/tetromino_tools)
add_subdirectory(src/operation)
add_subdirectory(src/time_event_system)

# plugins
add_subdirectory(plugins/console_player)

# test instance
# add_subdirectory(test/test_block_matrix)
# add_subdirectory(test/test_rotate)
# add_subdirectory(test/test_adjacent_states)
# add_subdirectory(test/test_bit_mask)
# add_subdirectory(test/test_tetromino_tools)
add_subdirectory(test/test_console_player)

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
        PRIVATE bit_mask
        PRIVATE tetromino_tools
        PRIVATE operation
        PRIVATE time_event_system

        # plugins
        PRIVATE console_player

        # test instance
#       PRIVATE test_block_matrix
#       PRIVATE test_rotate
#       PRIVATE test_adjacent_states
#       PRIVATE test_bit_mask
#       PRIVATE test_tetromino_tools
        PRIVATE test_console_player
)
