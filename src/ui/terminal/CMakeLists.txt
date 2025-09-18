add_library(console_player
        console_player.cpp
)

target_include_directories(console_player
        PUBLIC ../../../include
        PRIVATE .
)

target_link_libraries(console_player

)