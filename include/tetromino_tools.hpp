//
// Created by pilip on 2025/9/10.
//

#ifndef TETRIS_TETROMINO_TOOLS_HPP
#define TETRIS_TETROMINO_TOOLS_HPP

#include <random>
#include "tetromino.hpp"

/**
 *
 */
class TetrominoGenerator {
public:
    /**
     * @brief a tool function to generate a new tetromino with random type
     * @param matrix_pair ( @c MatrixAdjacentStates* )
     * @return @c Tetromino a constructed tetromino
     */
    static Tetromino new_tetromino(MatrixAdjacentStates * matrix_pair) noexcept;

private:
    // random number engine
    static std::mt19937 rng;
    // the distribution
    static std::uniform_int_distribution<int> dist;

    /**
     * @brief get a random tetromino type by the random number generator
     * @return @c TetrominoType
     * @see used in function @c new_tetromino()
     */
    static TetrominoType get_random_type() noexcept;
};


#endif //TETRIS_TETROMINO_TOOLS_HPP
