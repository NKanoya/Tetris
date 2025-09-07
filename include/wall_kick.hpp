//
// Created by pilip on 2025/9/6.
//

#ifndef TETRIS_WALL_KICK_HPP
#define TETRIS_WALL_KICK_HPP

#include "rotate.hpp"

/**
 * stores a list (composed of 4 axis) of wall-kick displacement to attempt
 */
using WallKickAttemptList = std::array<Axis, 4>;

/**
 * @brief singals the state of rotation
 *
 * used specifically to select the appropriate wall-kick strategy
 */
enum class RotateState {
    angle_0,
    angle_90,
    angle_180,
    angle_270
};

/**
 * @brief get wall-kick displacement attempt list for normal tetrominoes, except for I/O Tetrominoes
 *
 * @see @c wall_kick_tetro_I()
 *
 * @param rotate_state (<code>RotateState</code>) the current rotate state
 * @param clockwise (@c bool): the direction of rotation
 * @return ( @c const WallKickAttemptList& ) the wall-kick attempt list for current state
 */
const WallKickAttemptList& wall_kick_normal(RotateState rotate_state, bool clockwise);

/**
 * @brief get wall-kick displacement attempt specifically for I-tetrominoes, except for I/O Tetrominoes
 *
 * @see @c wall_kick_tetro_I()
 *
 * @param rotate_state (<code>RotateState</code>) the current rotate state
 * @param clockwise (@c bool): the direction of rotation
 * @return ( @c const WallKickAttemptList& ) the wall-kick attempt list for current state
 */
const WallKickAttemptList& wall_kick_tetro_I(RotateState rotate_state, bool clockwise);

#endif //TETRIS_WALL_KICK_HPP
