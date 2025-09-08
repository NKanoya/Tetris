add_library(
        test_adjacent_states
        test_adjacent_states.cpp
)

target_include_directories(
        test_adjacent_states
        PUBLIC ../../test
        PUBLIC ../../include
)

#target_link_libraries(
#        test_double_buffer
#        PRIVATE double_buffer
#)