//
// Created by pilip on 2025/9/5.
//

#include "../../include/matrix.hpp"
#include "../../include/matrix_state_manager.hpp"
#include <mutex>



MatrixStateManager* MatrixStateManager::m_instance = nullptr;
std::mutex MatrixStateManager::m_mtx{};

MatrixStateManager& MatrixStateManager::instance() {
    if(m_instance == nullptr) {
        // std::lock_guard<std::mutex> lock(m_mtx);
        if(m_instance == nullptr) {
            m_instance = new MatrixStateManager();
        }
    }

    return *m_instance;
}

MatrixStateManager::~MatrixStateManager() {
    delete m_instance;
}

const BlockMatrix& MatrixStateManager::get_current_matrix() const noexcept {
    return m_running_matrix.read_current();
}

const BitMask& MatrixStateManager::get_modifies_bitmask() const noexcept {
    return m_modifies_bitmask;
}

void MatrixStateManager::update_modifies_bitmask() noexcept {
    m_running_matrix.reload_modifies_bitmask(m_modifies_bitmask);
}

Tetromino& MatrixStateManager::new_tetromino() noexcept {
    // call the replace_and_update() function of the tetrominoes queue
    return m_tetro_queue.replace_and_update(
                // - use the tool function TetrominoGenerator::new_tetromino to generate two tetrominoes
                // with random types
                // - pass the raw pointer of the MatrixAdjacentStates which possesses them
                std::move(TetrominoGenerator::new_tetromino(&m_running_matrix))
            );
}

MatrixStateManager::MatrixStateManager():
        m_running_matrix(),
        // create an updated bitmap with the same size of running matrix
        m_modifies_bitmask(BlockMatrixProperties::instance_read_only().x_size,
                           BlockMatrixProperties::instance_read_only().y_size),
        // initialize the tetrominoes queue
        // use the tool function TetrominoGenerator::new_tetromino to generate two tetrominoes with random types
        // pass the raw pointer of the MatrixAdjacentStates which possesses them
        m_tetro_queue(TetrominoGenerator::new_tetromino(&m_running_matrix),
                      TetrominoGenerator::new_tetromino(&m_running_matrix)) {}

/**
 * @implements methods of class @c MatrixAdjacentStates
 */

void MatrixAdjacentStates::reload_modifies_bitmask(BitMask& recording_bitmask) noexcept {
    // cover previous matrix with current state
    cover_previous(recording_bitmask);
    // track current matrix
    m_current -> track_tetro();
    // clear the updated-state matrix
    recording_bitmask.clear();
    // traverse all blocks in the matrix
    for(int i = 0; i < BlockMatrixProperties::instance_read_only().x_size; ++i) {
        for(int j = 0; j < BlockMatrixProperties::instance_read_only().y_size; ++j) {
            // check if the pixel changes
            if(m_current -> get_block(i,j) != m_previous -> get_block(i,j) )
                // record in the recording_bitmask
                recording_bitmask.mark_dirty(i,j);
        }
    }

}

void MatrixAdjacentStates::cover_previous(const BitMask& bit_mask) noexcept {
    for(int i = 0; i < BlockMatrixProperties::instance_read_only().x_size; ++i){
        for(int j = 0; j < BlockMatrixProperties::instance_read_only().y_size; ++j) {
            if(bit_mask.is_dirty(i,j)) {
                m_previous -> get_block(i,j) = m_current -> get_block(i,j);
            }
        }
    }
}



