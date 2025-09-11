add_library(tetromino_tools
        tetromino_tools.cpp
)

target_include_directories(tetromino_tools
        PUBLIC ../../include
)

target_link_libraries(tetromino_tools
        PRIVATE tetromino
)