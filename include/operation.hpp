//
// Created by pilip on 2025/9/13.
//

#ifndef TETRIS_OPERATION_HPP
#define TETRIS_OPERATION_HPP

enum class Operation {
    None,
    Left,
    Right,
    Down,
    Drop,
    RotateCW,     // rotate clockwise
    RotateCCW     // rotate counterclockwise
};

#endif //TETRIS_OPERATION_HPP
