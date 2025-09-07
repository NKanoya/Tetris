///
/// @file @c test/map/test_contianer.cpp
///

#include "../test_include.hpp"
#include "../../include/map.hpp"


namespace TetroTest {
    void test_map() {
        BlockMap bmap;

        bmap.get_block(1, 1) = TetrominoType::tetro_I;
        bmap.get_block(1, 2) = TetrominoType::tetro_I;
        bmap.get_block(1, 3) = TetrominoType::tetro_I;
        bmap.get_block(2, 1) = TetrominoType::tetro_I;

        try {
            for (int i = 0; i < block_map_properties.x_size; ++i) {
                for (int j = 0; j < block_map_properties.y_size; ++j) {
                    if (bmap.get_block(i, j) == TetrominoType::empty)
                        printf("  ");
                    else
                        printf("█▉");
                }
                printf("\n");
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
