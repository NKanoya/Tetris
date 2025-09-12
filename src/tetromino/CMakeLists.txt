add_library(tetromino
        tetromino.cpp
)

target_include_directories(tetromino
        PUBLIC ../../include
)

target_link_libraries(tetromino
        PRIVATE rotate
        PRIVATE wall_kick
        PRIVATE block_matrix
        PRIVATE matrix_state_manager
)