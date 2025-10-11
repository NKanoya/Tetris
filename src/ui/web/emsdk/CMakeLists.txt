add_library(web_emsdk
        emscripten.cpp
)

target_include_directories(
        web_emsdk
        PUBLIC ../emsdk
        PUBLIC ../../../../include
)

target_link_libraries(
        web_emsdk

        PRIVATE block_matrix
        PRIVATE tetromino
        PRIVATE rotate
        PRIVATE wall_kick
        PRIVATE bit_mask

        PRIVATE tetromino_tools
        PRIVATE operation
        PRIVATE matrix_state_manager
        # PRIVATE em_bind

)