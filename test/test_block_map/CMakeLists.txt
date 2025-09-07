add_library(
        test_block_matrix
        test_block_matrix.cpp
)

target_include_directories(
        test_block_matrix
        PUBLIC ../../test
        PUBLIC ../../include
)

target_link_libraries(
        test_block_matrix
        PRIVATE block_matrix
        PRIVATE tetromino
)