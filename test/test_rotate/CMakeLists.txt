add_library(
        test_rotate
        test_rotate.cpp
)

target_include_directories(
        test_rotate
        PUBLIC ../../test
        PUBLIC ../../include
)

target_link_libraries(
        test_rotate
        PRIVATE rotate
)