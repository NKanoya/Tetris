add_library(block_map
        map.cpp
)

target_include_directories(block_map
        PUBLIC ../../include
)

target_link_libraries(block_map
        PRIVATE tetromino
        PRIVATE rotate
        PRIVATE wall_kick

)