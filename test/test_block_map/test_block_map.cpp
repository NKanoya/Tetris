///
/// @file @c test/matrix/test_contianer.cpp
///

#include "../test_include.hpp"
#include "matrix.hpp"


namespace TetroTest {
    void test_matrix() {
        BlockMatrix bmatrix;

        bmatrix.get_block(1, 1) = TetrominoType::tetro_I;
        bmatrix.get_block(1, 2) = TetrominoType::tetro_I;
        bmatrix.get_block(1, 3) = TetrominoType::tetro_I;
        bmatrix.get_block(2, 1) = TetrominoType::tetro_I;

        try {
            for (int i = 0; i < bmatrix_prop.x_size; ++i) {
                for (int j = 0; j < bmatrix_prop.y_size; ++j) {
                    if (bmatrix.get_block(i, j) == TetrominoType::empty)
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
