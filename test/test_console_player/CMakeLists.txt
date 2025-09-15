add_library(
        test_console_player
        test_console_player.cpp
        ../../src/matrix_state_manager/matrix_state_manager.cpp
)

target_include_directories(
        test_console_player
        PUBLIC ../../plugins/console_player
        PUBLIC ../../test
        PUBLIC ../../include
)

target_link_libraries(
        test_console_player

        PRIVATE block_matrix
        PRIVATE tetromino
        PRIVATE rotate
        PRIVATE wall_kick
        PRIVATE bit_mask

        PRIVATE tetromino_tools
        PRIVATE operation
        PRIVATE matrix_state_manager

        PRIVATE console_player


)