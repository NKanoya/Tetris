cmake_minimum_required(VERSION 3.29)
project(Tetris)

set(CMAKE_TOOLCHAIN_FILE "D:/DevTools/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP_ON 0)

# core modules
add_subdirectory(src/core/matrix_state_manager)
add_subdirectory(src/core/block_matrix)
add_subdirectory(src/core/rotate)
add_subdirectory(src/core/wall_kick)
add_subdirectory(src/core/tetromino)
add_subdirectory(src/core/bit_mask)
add_subdirectory(src/core/tetromino_tools)
add_subdirectory(src/core/operation)
add_subdirectory(src/core/time_event_system)

# ui modules
# add_subdirectory(src/ui/terminal)
add_subdirectory(src/ui/web/emsdk)

# test instance
# add_subdirectory(test/test_block_matrix)
# add_subdirectory(test/test_rotate)
# add_subdirectory(test/test_adjacent_states)
# add_subdirectory(test/test_bit_mask)
# add_subdirectory(test/test_tetromino_tools)
# add_subdirectory(test/test_console_player)

add_executable(
        Tetris
        main.cpp
)

set_target_properties(Tetris PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../src/ui/web/js"
)

# find_library(EMBIND_LIB embind)

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
        PRIVATE web_emsdk

        # plugins
#       PRIVATE console_player

        # test instance
#       PRIVATE test_block_matrix
#       PRIVATE test_rotate
#       PRIVATE test_adjacent_states
#       PRIVATE test_bit_mask
#       PRIVATE test_tetromino_tools
#       PRIVATE test_console_player

        PRIVATE em_bind
)

target_link_options(Tetris PRIVATE
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s EXPORT_ES6=1"
        "SHELL:-s WASM=1"
        "SHELL:-s ALLOW_MEMORY_GROWTH=1"
        "SHELL:-s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
        "SHELL:-s EXPORTED_FUNCTIONS=['_main','_JS_process_loop']"
        "SHELL:--bind"
        "SHELL:-s EXCEPTION_CATCHING_ALLOWED=['c++']"
        "SHELL:-g"
        #"SHELL:-s DEMANGLE_SUPPORT=1"
)