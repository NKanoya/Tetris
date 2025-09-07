//
// Created by pilip on 2025/9/6.
//

#ifndef TETRIS_WALL_KICK_HPP
#define TETRIS_WALL_KICK_HPP

#include "rotate.hpp"

using WallKickAttemptList = std::array<Axis, 4>;

enum class RotateState {
    angle_0,
    angle_90,
    angle_180,
    angle_270
};

const WallKickAttemptList& wall_kick_normal(RotateState angle_state, bool clockwise);

const WallKickAttemptList& wall_kick_tetro_I(RotateState angle_state, bool clockwise);

#endif //TETRIS_WALL_KICK_HPP
