///
/// @file @c include/rotate.hpp
///

#ifndef TETRIS_ROTATE_HPP
#define TETRIS_ROTATE_HPP

#include <iostream>
#include <array>

struct Axis {
    ptrdiff_t x;
    ptrdiff_t y;
};

using BlockShape = std::array<Axis, 4>;



void eval_rotate_dest_I(const BlockShape& source, BlockShape& destination, bool clockwise = true);

void eval_rotate_dest_normal(const BlockShape& source, BlockShape& destination, bool clockwise = true);

#endif //TETRIS_ROTATE_HPP
