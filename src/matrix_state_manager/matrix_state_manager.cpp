//
// Created by pilip on 2025/9/5.
//

#include "../../include/matrix.hpp"
#include "../../include/matrix_state_manager.hpp"
#include "../../include/tetromino.hpp"



MatrixStateManager* MatrixStateManager::m_instance = nullptr;
std::mutex MatrixStateManager::m_mtx{};

MatrixStateManager& MatrixStateManager::instance() {
    if(m_instance == nullptr) {
        std::lock_guard<std::mutex> lock(m_mtx);
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
    return m_current_matrix;
}

const BlockMatrix& MatrixStateManager::get_updated_matrix() const noexcept {
    return m_last_matrix;
}

void MatrixStateManager::update() noexcept {
    m_last_matrix = std::move(m_current_matrix);
    // track tetro
    m_current_matrix.track_tetro();
    //
    for(size_t i = 0; i < bmatrix_prop.x_size; ++i)
        for(size_t j = 0; j < bmatrix_prop.y_size; ++j) {
            if(m_last_matrix.get_block(i,j) != m_current_matrix.get_block(i,j))
                // check updated blocks
                m_updated.get_block(i,j) = m_current_matrix.get_block(i,j);
        }

}


