//
// Created by pilip on 2025/9/5.
//

#include "../../include/matrix.hpp"
#include "../../include/matrix_state_manager.hpp"
#include <mutex>

std::mutex MatrixStateManager::m_mtx{};

MatrixStateManager& MatrixStateManager::instance() {
    static MatrixStateManager instance;
    return instance;
}

MatrixStateManager::~MatrixStateManager() = default;

const RunningBlockMatrix& MatrixStateManager::get_current_matrix() const noexcept {
    return m_running_matrix.read_current();
}

const BitMask& MatrixStateManager::get_modifies_bitmask() const noexcept {
    return m_modifies_bitmask;
}

size_t MatrixStateManager::update_modifies_bitmask() noexcept {
    return m_running_matrix.reload_modifies_bitmask(m_modifies_bitmask);
}

Tetromino& MatrixStateManager::new_tetromino() noexcept {
    // call the replace_and_update() function of the tetrominoes queue
    auto& return_tetro =
                m_tetro_queue.replace_and_update(
                    // - use the tool function TetrominoGenerator::new_tetromino to generate two tetrominoes
                    // with random types
                    // - pass the raw pointer of the MatrixAdjacentStates which possesses them
                    std::move(TetrominoGenerator::new_tetromino(&m_running_matrix))
                );

    m_running_matrix;

    // update the info of the tetromino in the matrix pair
    m_running_matrix.update_tetro_in_matrix_pair(m_tetro_queue.get_tetromino_shared_ptr());

    return return_tetro;
}

MatrixStateManager::MatrixStateManager():
        // initialize the tetrominoes queue
        // use the tool function TetrominoGenerator::new_tetromino to generate two tetrominoes with random types
        // pass the raw pointer of the MatrixAdjacentStates which possesses them
        m_tetro_queue(TetrominoGenerator::new_tetromino(&m_running_matrix),
                      TetrominoGenerator::new_tetromino(&m_running_matrix)),
        m_running_matrix(RunningBlockMatrix(m_tetro_queue.get_tetromino_shared_ptr())),
        // create an updated bitmap with the same size of running matrix
        m_modifies_bitmask(BlockMatrixProperties::instance_read_only().x_size,
                           BlockMatrixProperties::instance_read_only().y_size)
        {}

bool MatrixStateManager::is_current_tetro_bottom_out() const noexcept {
    return m_tetro_queue.is_current_bottom_out();
}

bool MatrixStateManager::check_failed(size_t return_value) const noexcept {
    if(return_value == BlockMatrixProperties::instance_read_only().check_failed_signal)
        return m_running_matrix.read_current().is_game_over();

    return false;
}

MatrixStateManager::ProcessData MatrixStateManager::process_operation(Operation op) noexcept {
    switch(op) {
        case Operation::Drop:
            m_tetro_queue.get_current().drop();
            break;
        case Operation::Left:
            m_tetro_queue.get_current().move_leftward();
            break;
        case Operation::Right:
            m_tetro_queue.get_current().move_rightward();
            break;
        case Operation::RotateCW:
            m_tetro_queue.get_current().rotate(true);
            break;
        case Operation::RotateCCW:
            m_tetro_queue.get_current().rotate(false);
            break;
        default:
            m_tetro_queue.get_current().move_downwards();
            break;
    }

    auto return_value = update_modifies_bitmask();

    if(is_current_tetro_bottom_out()) {
        // the game failed;
        if(check_failed(return_value)) {
            if(is_current_tetro_bottom_out()) {
                // TODO: add the logic of game failed

                update_modifies_bitmask();
                return {get_modifies_bitmask(), get_current_matrix(), 0, true};
            }
        }

        // generate a new tetromino
        new_tetromino();
        size_t cleared_rows = update_modifies_bitmask();
        return {m_modifies_bitmask, get_current_matrix(), cleared_rows,false};
    }

    return {get_modifies_bitmask(), get_current_matrix(), 0,false};
}


/**
 * @implements methods of class @c MatrixAdjacentStates
 */

size_t MatrixAdjacentStates::reload_modifies_bitmask(BitMask& recording_bitmask) noexcept {
    // cover previous matrix with current state
    cover_previous(recording_bitmask);
    // track current matrix
    auto cleared_rows = m_current -> track_tetro();
    // clear the updated-state matrix
    recording_bitmask.clear();
    // traverse all blocks in the matrix
    for(size_t i = 0; i < BlockMatrixProperties::instance_read_only().x_size; ++i) {
        for(size_t j = 0; j < BlockMatrixProperties::instance_read_only().y_size; ++j) {
            // check if the pixel changes
            if((m_current -> get_block(i,j)) != (m_previous -> get_block(i,j)) )
                // record in the recording_bitmask
                recording_bitmask.mark_dirty(i,j);
        }
    }

    return cleared_rows;

}

void MatrixAdjacentStates::cover_previous(const BitMask& bit_mask) noexcept {
    for(size_t i = 0; i < BlockMatrixProperties::instance_read_only().x_size; ++i){
        for(size_t j = 0; j < BlockMatrixProperties::instance_read_only().y_size; ++j) {
            if(bit_mask.is_dirty(i,j)) {
                m_previous -> get_block(i,j) = m_current -> get_block(i,j);
            }
        }
    }

    // TODO: refactor this to avoid copy (e.g. make these shared between states)
    m_previous -> m_completed_rows_number = m_current -> m_completed_rows_number;
    m_previous -> m_completed_rows = m_current -> m_completed_rows;
    m_previous -> m_over_buffer = m_current -> m_over_buffer;
}

void MatrixAdjacentStates::update_tetro_in_matrix_pair(const std::shared_ptr<Tetromino>& new_tetro_ptr) noexcept {
    m_current -> m_tetro = new_tetro_ptr;
    m_current -> m_tetro_type = new_tetro_ptr -> get_type();

    // update the pointer and the type records of the tetromino
    m_previous -> m_tetro = m_current -> m_tetro;
    m_previous -> m_tetro_type = m_current -> m_tetro_type;
}


