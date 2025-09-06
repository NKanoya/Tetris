add_library(
        test_block_map
        test_block_map.cpp
)

target_include_directories(
        test_block_map
        PUBLIC ../test_include.hpp
)

target_link_libraries(
        test_block_map
        PRIVATE block_map
)