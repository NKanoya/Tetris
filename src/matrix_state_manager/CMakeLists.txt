add_library(matrix_state_manager
        matrix_state_manager.cpp
)

target_include_directories(matrix_state_manager
        PUBLIC ../../include
)

target_link_libraries(matrix_state_manager
        PRIVATE tetromino
        PRIVATE block_matrix
        PRIVATE rotate
        PRIVATE wall_kick
        PRIVATE bit_mask

)