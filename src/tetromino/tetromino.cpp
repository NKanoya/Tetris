///
/// @file @c src/tetromino/tetromino.cpp
///

#include "tetromino.hpp"

static constexpr std::array<BlockShape, 7> tetromino_shape = {{
      /*
       * O Tetromino
       * TetrominoType::tetro_O
       *
       * ··█▉█▉··
       * ··█▉█▉··
       * ········
       * ········
       */
      {{{1,1},{0, 0}, {0, 1}, {1, 0}}},

      /*
       *
       * I Tetromino
       * TetrominoType::tetro_I
       *
       * ········
       * █▉█▉█▉█▉
       * ········
       * ········
       */
      {{{1,1},{1, 0}, {1, 2}, {1, 3}}},

      /*
      * T Tetromino
      * TetrominoType::tetro_T
      *
      * ··█▉····
      * █▉█▉█▉··
      * ········
      * ········
      */
      {{{1,1},{0, 1}, {1, 0}, {1, 2}}},

      /*
       * J Tetromino
       * TetrominoType::tetro_J
       *
       * █▉······
       * █▉█▉█▉··
       * ········
       * ········
       */
      {{{1,1},{0, 0}, {1, 0}, {1, 2}}},

      /*
       * L Tetromino
       * TetrominoType::tetro_L
       *
       * ····█▉··
       * █▉█▉█▉··
       * ········
       * ········
       */
      {{{1,1},{0, 2}, {1, 0}, {1, 2}}},

      /*
       * S Tetromino
       * TetrominoType::tetro_S
       *
       * ··█▉█▉··
       * █▉█▉····
       * ········
       * ········
       */
      {{{1,1},{0, 1}, {0, 2}, {1, 0}}},

      /*
      * Z Tetromino
      * TetrominoType::tetro_Z
      *
      * █▉█▉····
      * ··█▉█▉··
      * ········
      * ········
      */
      {{{1,1},{0, 0}, {0, 1}, {1, 2}}},
}};

static constexpr BlockShape get_init_shape(TetrominoType type) noexcept {
    return tetromino_shape[static_cast<int>(type) - 1];
}

Tetromino::Tetromino(TetrominoType type, const Axis& axis, RunningBlockMatrix * BlockMatrix) noexcept
    : m_axis(axis),
      m_BlockMatrix(BlockMatrix),
      m_rotate_state(RotateState::angle_0)
{
    if(type == TetrominoType::empty){
        // TODO: print warning info into log
        type = TetrominoType::tetro_O;
    }

    m_type = type;
    m_blocks = get_init_shape(type);

}

void Tetromino::fall() noexcept {
    if(m_axis.x + 4 == bmatrix_prop.y_size){
        // the tetromino is bottoming out
        // notify the block matrix that the tetromino belongs to
        m_BlockMatrix -> bottom_out();
    }

    // bound check: check if the tetromino have space below
    bool have_space_below = false;
    for(Axis& block: m_blocks){
        auto checked_x = m_axis.x + block.x + 1;
        auto checked_y = m_axis.y + block.x;
        if(m_BlockMatrix -> get_block(checked_x, checked_y) != TetrominoType::empty){
            have_space_below = true;
            break;
        }
    }

    if(have_space_below){
        // the tetromino is bottoming out
        // notify the block matrix that the tetromino belongs to
        m_BlockMatrix -> bottom_out();
    } else {
        // simply increase the y-axis by 1
        ++m_axis.x;
    }
}

void Tetromino::move_leftward() noexcept {
    // bound check
    if(m_axis.y == 0)
        return;         // fail to move

    // check if there is space on the left
    bool have_space_on_left = true;
    // traverse all blocks
    for(Axis& block: m_blocks){
        auto checked_x = m_axis.x + block.x;
        auto checked_y = m_axis.y + block.y - 1;
        if(m_BlockMatrix -> get_block(checked_x, checked_y) != TetrominoType::empty){
            have_space_on_left = false;
            break;
        }
    }

    if(have_space_on_left){
        --m_axis.y;       // decrease the x-axis by 1
    }
    // otherwise, fail to move
}

void Tetromino::move_rightward() noexcept {
    // bound check
    if(m_axis.y + 4 == bmatrix_prop.x_size)
        return;         // fail to move

    // check if there is space on the right
    bool have_space_on_right = true;
    // traverse all blocks
    for(Axis& block: m_blocks){
        auto checked_x = m_axis.x + block.x;
        auto checked_y = m_axis.y + block.y + 1;
        if(m_BlockMatrix -> get_block(checked_x, checked_y) != TetrominoType::empty){
            have_space_on_right = false;
            break;
        }
    }

    if(have_space_on_right){
        ++m_axis.y;       // decrease the y-axis by 1
    }
    // otherwise, fail to move
}

void Tetromino::rotate(bool clockwise) noexcept {
    if(m_type == TetrominoType::tetro_O) return;

    BlockShape destination;
    bool is_rotation_blocked = false;

    if(m_type == TetrominoType::tetro_I) {
        eval_rotate_dest_I(m_blocks, destination, clockwise);
    } else {
        eval_rotate_dest_normal(m_blocks, destination, clockwise);
    }
    // traverse the block to check if any blocked
    for(auto& dest_axis: destination) {
        // if the rotation is
        if(m_BlockMatrix -> get_block(dest_axis.x,dest_axis.y) != TetrominoType::empty) {
            is_rotation_blocked = true;
            break;
        }
    }

    // if the rotation is not blocked
    if(!is_rotation_blocked) {
        employ_rotation(destination, clockwise);
        return;
    }

    // else: employ wall-kick displacement
    if(m_type == TetrominoType::tetro_I) {
        // get wall-kick attempt list
        auto& attempt_list = wall_kick_tetro_I(m_rotate_state,clockwise);
        // traverse the attempt list
        for(auto& displacement_axis: attempt_list) {
            // check all
            if(check_space_for_wall_kick(destination, displacement_axis)) {
                // add wall-kick displacement to the destination
                for(auto& axis: destination) {
                    axis_displace(axis, displacement_axis);
                }
                // employ the rotation
                employ_rotation(destination);
            }
        }

        // otherwise, the rotation fails

    } else {

        // get wall-kick attempt list
        auto& attempt_list = wall_kick_normal(m_rotate_state,clockwise);
        // traverse the attempt list
        for(auto& displacement_axis: attempt_list) {
            // check all
            if(check_space_for_wall_kick(destination, displacement_axis)) {
                // add wall-kick displacement to the destination
                for(auto& axis: destination) {
                    axis_displace(axis, displacement_axis);
                }
                // employ the rotation
                employ_rotation(destination);
            }
        }

        // otherwise, the rotation fails

    }
}

void Tetromino::change_rotate_state(RotateState &rotate_state, bool clockwise) noexcept {
    if (clockwise) {
        int target = static_cast<int>(rotate_state) + 1;
        if(target >= 3) {
            target = 0;
        }
        rotate_state = static_cast<RotateState>(target);
        return;
    }
    else {
        int target = static_cast<int>(rotate_state) - 1;
        if(target <= 0) {
            target = 3;
        }
        rotate_state = static_cast<RotateState>(target);
        return;
    }
}

void Tetromino::employ_rotation(const BlockShape &destination, bool clockwise) noexcept {
    change_rotate_state(m_rotate_state, clockwise);
    m_blocks = destination;
}

bool Tetromino::check_space_for_wall_kick(const BlockShape &origin_dest, const Axis& wall_kick_disp) const noexcept {
    for(auto& axis: origin_dest) {
        auto checked_x = axis.x + wall_kick_disp.x;
        auto checked_y = axis.y + wall_kick_disp.y;

        if(m_BlockMatrix -> get_block(checked_x,checked_y) != TetrominoType::empty) {
            return false;
        }
    }
    return true;
}

void Tetromino::axis_displace(Axis &origin_axis, const Axis &displacement) {
    origin_axis.x += displacement.x;
    origin_axis.y += displacement.y;
}






