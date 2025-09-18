add_library(wall_kick
        wall_kick.cpp
)

target_include_directories(wall_kick
        PUBLIC ../../../include
)

target_link_libraries(wall_kick
        PRIVATE rotate
)