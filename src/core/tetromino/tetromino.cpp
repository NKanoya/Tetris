///
/// @file @c src/tetromino/tetromino.cpp
///

#include "tetromino.hpp"
#include "../../../include/matrix_state_manager.hpp"

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

Tetromino::Tetromino(TetrominoType type, const Axis& axis, MatrixAdjacentStates * matrix_pair) noexcept
    : m_matrix_state_pair(matrix_pair),
      m_rotate_state(RotateState::angle_0),
      m_type(type == TetrominoType::empty?(TetrominoType::tetro_O):type),
      m_position(axis, get_init_shape(m_type)),
      m_is_bottom_out(false)
{
    // TODO: print warning info into log
}

static bool have_below_space(AdjacentStates<TetrominoPosition>& position_pair, MatrixAdjacentStates* matrix_pair);

void Tetromino::move_downwards() noexcept {
    // bound check: check if the tetromino have space below
    if(have_below_space(m_position,m_matrix_state_pair)) {
        // simply increase the x-axis by 1
        using TetroPosPtr = std::unique_ptr<TetrominoPosition>;
        m_position.update_current(
                [](TetroPosPtr& previous, TetroPosPtr& current){
                    *previous = *current;
                },
            [](TetrominoPosition& position){
                ++position.axis.x;
            }
        );

    } else {
        m_is_bottom_out = true;
    }
}


void Tetromino::drop() noexcept {
    // move downwards until bottoming out
    bool first_record = true;
    while(have_below_space(m_position,m_matrix_state_pair)) {
        using TetroPosPtr = std::unique_ptr<TetrominoPosition>;
        m_position.update_current(
                [&first_record](TetroPosPtr& previous, TetroPosPtr& current){
                    if(first_record) {
                        // ensure the `previous` member is only recorded once
                        *previous = *current;
                        first_record = false;
                    }
                    // no update
                },
                [](TetrominoPosition& position){
                    ++position.axis.x;
                }
        );
    }
    m_is_bottom_out = true;
}

static bool have_below_space(AdjacentStates<TetrominoPosition>& position_pair, MatrixAdjacentStates* matrix_pair) {
    // get the properties
    auto& prop = BlockMatrixProperties::instance();
    // traverse coordinates of all blocks in the tetromino
    for(auto& block: position_pair.read_current().blocks){
        auto checked_x = position_pair.read_current().axis.x + block.x + 1;
        auto checked_y = position_pair.read_current().axis.y + block.y;
        // bound check: if the tetromino overflows
        if(checked_x >= prop.x_size || checked_x < 0) {
            return false;
        }
        // if the destination is blocked by existing tetromino
        auto tetro = matrix_pair -> read_current().get_block(checked_x, checked_y);
        if(tetro != TetrominoType::empty && tetro != TetrominoType::tetro_active){
            return false;
        }
    }
    return true;
}

void Tetromino::move_leftward() noexcept {

    auto& prop = BlockMatrixProperties::instance();
    // check if there is space on the left
    bool have_space_on_left = true;
    // traverse all blocks
    for(auto& block: m_position.read_current().blocks){
        auto checked_x = m_position.read_current().axis.x + block.x;
        auto checked_y = m_position.read_current().axis.y + block.y - 1;
        if(checked_y >= prop.y_size || checked_y < 0) {
            have_space_on_left = false;
            break;
        }
        auto target = m_matrix_state_pair -> read_current().get_block(checked_x, checked_y);
        if((target != TetrominoType::tetro_active) && (target != TetrominoType::empty)){
            have_space_on_left = false;
            break;
        }
    }

    if(have_space_on_left){
        using TetroPosPtr = std::unique_ptr<TetrominoPosition>;
        // decrease the y-axis by 1
        m_position.update_current(
                [](TetroPosPtr& previous, TetroPosPtr& current){
                    *previous = *current;
                },
                [](TetrominoPosition& position){
                    --position.axis.y;
                }
        );
    }
    // otherwise, fail to move
}

void Tetromino::move_rightward() noexcept {
    // bound check
    auto& prop = BlockMatrixProperties::instance();

    // check if there is space on the right
    bool have_space_on_right = true;
    // traverse all blocks
    for(auto& block: m_position.read_current().blocks){
        auto checked_x = m_position.read_current().axis.x + block.x;
        auto checked_y = m_position.read_current().axis.y + block.y + 1;
        if(checked_y >= prop.y_size || checked_y < 0) {
            have_space_on_right = false;
            break;
        }
        auto target = m_matrix_state_pair -> read_current().get_block(checked_x, checked_y);
        if((target != TetrominoType::tetro_active) && (target != TetrominoType::empty)){
            have_space_on_right = false;
            break;
        }
    }

    if(have_space_on_right){
        // increase the y-axis by 1
        using TetroPosPtr = std::unique_ptr<TetrominoPosition>;
        m_position.update_current(
                [](TetroPosPtr& previous, TetroPosPtr& current){
                    *previous = *current;
                },
                [](TetrominoPosition& position){
                    ++position.axis.y;
                }
        );
    }
    // otherwise, fail to move
}

void Tetromino::rotate(bool clockwise) noexcept {
    if(m_type == TetrominoType::tetro_O) return;

    BlockShape destination;
    bool is_rotation_blocked = false;

    if(m_type == TetrominoType::tetro_I) {
        eval_rotate_dest_I(m_position.read_current().blocks, destination, clockwise);
    } else {
        eval_rotate_dest_normal(m_position.read_current().blocks, destination, clockwise);
    }
    // traverse the block to check if any blocked
    for(auto dest_axis: destination) {
        // calculate the absolute axis (of the whole matrix) of the destination
        auto abs_axis = m_position.read_current().axis;
        dest_axis.x += abs_axis.x;
        dest_axis.y += abs_axis.y;

        if(dest_axis.x >= bmatrix_prop.x_size || dest_axis.x < 0 ||
           dest_axis.y >= bmatrix_prop.y_size || dest_axis.y < 0) {
            is_rotation_blocked = true;
            break;
        }
        auto target = m_matrix_state_pair -> read_current().get_block(dest_axis.x,dest_axis.y);
        if((target != TetrominoType::tetro_active) && (target != TetrominoType::empty)) {
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
            // calculate the absolute axis (of the whole matrix) of the destination
            auto& abs_axis = m_position.read_current().axis;
            // check all
            if(check_space_for_wall_kick(abs_axis,destination, displacement_axis)) {
                // add wall-kick displacement to the destination
                for(auto& axis: destination) {
                    axis_displace(axis, displacement_axis);
                }
                // employ the rotation
                employ_rotation(destination);
                break;
            }
        }

        // otherwise, the rotation fails

    } else {

        // get wall-kick attempt list
        auto& attempt_list = wall_kick_normal(m_rotate_state,clockwise);
        // traverse the attempt list
        for(auto& displacement_axis: attempt_list) {
            // check all
            auto& abs_axis = m_position.read_current().axis;
            if(check_space_for_wall_kick(abs_axis, destination, displacement_axis)) {
                // add wall-kick displacement to the destination
                for(auto& axis: destination) {
                    axis_displace(axis, displacement_axis);
                }
                // employ the rotation
                employ_rotation(destination);
                break;
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

    using TetroPosPtr = std::unique_ptr<TetrominoPosition>;
    m_position.update_current(
            [](TetroPosPtr& previous, TetroPosPtr& current){
                *previous = *current;
            },
            [&destination](TetrominoPosition& position){
                position.blocks = destination;
            }
    );
}

bool Tetromino::check_space_for_wall_kick(const Axis& abs_axis, const BlockShape &origin_dest, const Axis& wall_kick_disp) const noexcept {
    for(auto& axis: origin_dest) {
        auto checked_x = abs_axis.x + axis.x + wall_kick_disp.x;
        auto checked_y = abs_axis.y + axis.y + wall_kick_disp.y;
        if(checked_x >= bmatrix_prop.x_size || checked_x < 0)
            return false;
        if(checked_y >= bmatrix_prop.y_size || checked_y < 0)
            return false;

        auto checked_block = m_matrix_state_pair -> read_current().get_block(checked_x,checked_y);
        if(checked_block != TetrominoType::empty
         && checked_block != TetrominoType::tetro_active) {
            return false;
        }
    }
    return true;
}

void Tetromino::axis_displace(Axis &origin_axis, const Axis &displacement) {
    origin_axis.x += displacement.x;
    origin_axis.y += displacement.y;
}








