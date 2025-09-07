//
// Created by pilip on 2025/9/7.
//

#ifndef TETRIS_MATRIX_STATE_MANAGER_HPP
#define TETRIS_MATRIX_STATE_MANAGER_HPP

#include "matrix.hpp"




/*
 * @brief A @b singleton class, recording blocks states in every ticks
 *
 * including current block matrix, block matrix at last tick, and the updated block matrix (signalling which blocks
 * have benn updated in this tick)
 */
class MatrixStateManager {
public:
    // use the instance
    static MatrixStateManager& instance();

    const BlockMatrix& get_current_matrix() const noexcept;
    const BlockMatrix& get_updated_matrix() const noexcept;

    void update() noexcept;

public:

    MatrixStateManager(const MatrixStateManager& ms) = delete;
    MatrixStateManager& operator==(const MatrixStateManager& ms) = delete;

private:
    // Singleton properties
    static MatrixStateManager* m_instance;
    static std::mutex m_mtx;

    // private constructor
    MatrixStateManager(): m_current_matrix(), m_last_matrix(), m_updated() {}

    RunningBlockMatrix m_current_matrix;
    RunningBlockMatrix m_last_matrix;
    BlockMatrix m_updated;

    ~MatrixStateManager();
};

#endif //TETRIS_MATRIX_STATE_MANAGER_HPP
