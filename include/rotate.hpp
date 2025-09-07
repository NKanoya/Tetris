///
/// @file @c include/rotate.hpp
///

#ifndef TETRIS_ROTATE_HPP
#define TETRIS_ROTATE_HPP

#include <iostream>
#include <array>


/**
 * @struct @c Axis
 *
 * a simple axis structure
 *
 * used for both blocks coordinate (compulsorily non-negative) and coordinate displacement
 *
 * @note positive @b Y-axis points to the @b right
 * @note positive @b X-axis points @b downward.
 */
struct Axis {
    ptrdiff_t x;
    ptrdiff_t y;
};

/**
 * @typedef @c BlockShape
 *
 * composed of 4 axis relative to the 4x4 grid, defines the relative positions of the tetrimino's four
 * blocks based on the 4x4 framework.
 */
using BlockShape = std::array<Axis, 4>;

/**
 * <p> Evaluates the destination of this rotating operation, specifically for @b I-Tetrominoes
 *
 * <p> Computes expected post-rotation coordinates into reference @c destination .
 *
 * @note @c source and @c destination should be different arrays, otherwise the function will return directly.
 * @note @b Pure: this function won't mutate original array or rotation state.
 *
 * @param source <code>const BlockShape&</code> : the shape of the I before rotation
 * @param destination @c BlockShape& : receive the destination shape after rotation
 * @param clockwise @c bool (@b default: @c true ) : whether the rotation is performed in a clockwise direction
 *
 * @see @c eval_rotate_dest_normal() : for other tetrominoes
 */
void eval_rotate_dest_I(const BlockShape& source, BlockShape& destination, bool clockwise = true);

/**
 * <p> Evaluates the destination of this rotating operation for tetrominoes <b>except for I-Tetrominoes
 * or O-Tetrominoes </b>
 *
 * <p> Computes expected post-rotation coordinates into reference @c destination .
 *
 * @note @c source and @c destination should be different arrays, otherwise the function will return directly.
 * @note @b Pure: this function won't mutate original array or rotation state.
 *
 * @param source <code>const BlockShape&</code> : the shape of the I before rotation
 * @param destination @c BlockShape& : receive the destination shape after rotation
 * @param clockwise @c bool (@b default: @c true ) : whether the rotation is performed in a clockwise direction
 *
 * @see @c eval_rotate_dest_normal() : for other tetrominoes
 */
void eval_rotate_dest_normal(const BlockShape& source, BlockShape& destination, bool clockwise = true);

#endif //TETRIS_ROTATE_HPP
