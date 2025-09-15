add_library(
        test_console_output
        test_console_output.cpp
        ../../src/matrix_state_manager/matrix_state_manager.cpp
)

target_include_directories(
        test_console_output
        PUBLIC ../../plugins/console_output
        PUBLIC ../../test
        PUBLIC ../../include
)

target_link_libraries(
        test_console_output

        PRIVATE block_matrix
        PRIVATE tetromino
        PRIVATE rotate
        PRIVATE wall_kick
        PRIVATE bit_mask

        PRIVATE tetromino_tools
        PRIVATE operation
        PRIVATE matrix_state_manager

        PRIVATE console_output


)