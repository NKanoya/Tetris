add_library(
        test_bit_mask
        test_bit_mask.cpp
)

target_include_directories(
        test_bit_mask
        PUBLIC ../../test
        PUBLIC ../../include
)

target_link_libraries(
        test_bit_mask
        PRIVATE bit_mask
)