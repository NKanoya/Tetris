//
// Created by pilip on 2025/9/5.
//

#include "../../include/matrix.hpp"
#include "../../include/matrix_state_manager.hpp"
#include "../../include/tetromino.hpp"
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

const BitMask& MatrixStateManager::get_updated_matrix() const noexcept {
    return m_updated_matrix;
}

void MatrixStateManager::update_matrix() noexcept {
    m_running_matrix.compare_map(m_updated_matrix);
}

void MatrixStateManager::generate_tetromino() noexcept {
    m_running_matrix.;
}


/**
 * @implements methods of class @c MatrixAdjacentStates
 */

void MatrixAdjacentStates::compare_map(BitMask& updated_recording_matrix) noexcept {
    // cover previous matrix with current state
    cover_previous(updated_recording_matrix);
    // track current matrix
    m_current -> track_tetro();
    // clear the updated-state matrix
    updated_recording_matrix.clear();
    // traverse all blocks in the matrix
    for(int i = 0; i < BlockMatrixProperties::instance_read_only().x_size; ++i) {
        for(int j = 0; j < BlockMatrixProperties::instance_read_only().y_size; ++j) {
            // check if the pixel changes
            if(m_current -> get_block(i,j) != m_previous -> get_block(i,j) )
                // record in the updated_recording_matrix
                updated_recording_matrix.mark_dirty(i,j);
        }
    }
}

void MatrixAdjacentStates::cover_previous(BitMask& bit_mask) noexcept {
    for(int i = 0; i < BlockMatrixProperties::instance_read_only().x_size; ++i){
        for(int j = 0; j < BlockMatrixProperties::instance_read_only().y_size; ++j) {
            if(bit_mask.is_dirty(i,j)) {
                m_previous -> get_block(i,j) = m_current -> get_block(i,j);
            }
        }
    }
}




