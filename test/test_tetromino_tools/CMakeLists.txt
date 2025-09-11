add_library(test_tetromino_tools
        test_tetromino_tools.cpp
)

target_include_directories(test_tetromino_tools
        PUBLIC ../../include
        PUBLIC ../../test
)

target_link_libraries(test_tetromino_tools
        PRIVATE tetromino
        PRIVATE tetromino_tools
)