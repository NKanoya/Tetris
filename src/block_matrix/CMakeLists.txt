add_library(block_matrix
        matrix.cpp
)

target_include_directories(block_matrix
        PUBLIC ../../include
)

target_link_libraries(block_matrix
        PRIVATE tetromino
        PRIVATE rotate
        PRIVATE wall_kick
        PRIVATE matrix_state_manager

)