add_library(
        test_double_buffer
        test_double_buffer.cpp
)

target_include_directories(
        test_double_buffer
        PUBLIC ../../test
        PUBLIC ../../include
)

#target_link_libraries(
#        test_double_buffer
#        PRIVATE double_buffer
#)