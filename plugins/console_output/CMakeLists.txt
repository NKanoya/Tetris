add_library(console_output
        console_output.cpp
)

target_include_directories(console_output
        PUBLIC ../../include
        PRIVATE ../console_output
)

target_link_libraries(console_output

)