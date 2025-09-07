///
/// @file @c src/rotate/rotate.cpp
///

#include "../../include/wall_kick.hpp"

static const std::array<const WallKickAttemptList, 4> wall_kick_attempts_for_normal = {{
     // state: 0 -> 90    || 180 -> 90
     {{{-1,0},{-1,1},{0,-2},{-1,-2}}},
     // state: 90 -> 180  || 90 -> 0
     {{{1,0},{+1,-1},{0,+2},{+1,+2}}},
     // state: 180 -> 270 || 0 -> 270
     {{{1,0},{1,1},{0,-2},{+1,-2}}},
     // state: 270 -> 0   || 270 -> 180
     {{{-1,0},{-1,-1},{0,2},{-1,2}}}
}};

static const std::array<const WallKickAttemptList, 4> wall_kick_attempts_for_tetro_I = {{
    // state: 0 -> 90    || 270 -> 180
    {{{-2,0},{1,0},{-2,-1},{1,2}}},
    // state: 90 -> 180  || 0 -> 270
    {{{-1,0},{2,0},{-1,+2},{2,-1}}},
    // state: 180 -> 270 || 90 -> 0
    {{{2,0},{-1,0},{2,1},{-1,-2}}},
    // state: 270 -> 0   || 180 -> 90
    {{{1,0},{-2,0},{1,-2},{-2,1}}}
}};

const WallKickAttemptList& wall_kick_normal(RotateState angle_state, bool clockwise) {
    if(clockwise) {
        return wall_kick_attempts_for_normal[static_cast<size_t>(angle_state)];
    } else {
        if(angle_state == RotateState::angle_270)
            return wall_kick_attempts_for_normal[3];
        else
            return wall_kick_attempts_for_normal[2 - static_cast<size_t>(angle_state)];
    }
}


const WallKickAttemptList& wall_kick_tetro_I(RotateState angle_state, bool clockwise) {
    if(clockwise) {
        return wall_kick_attempts_for_normal[static_cast<size_t>(angle_state)];
    } else {
        if(angle_state == RotateState::angle_270)
            return wall_kick_attempts_for_normal[0];
        else
            return wall_kick_attempts_for_normal[static_cast<size_t>(angle_state) + 1];
    }
}
