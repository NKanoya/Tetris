//
// Created by pilip on 2025/9/7.
//

#ifndef TETRIS_MATRIX_STATE_MANAGER_HPP
#define TETRIS_MATRIX_STATE_MANAGER_HPP

#include "matrix.hpp"
#include "bit_mask.hpp"
#include "adjacent_states.hpp"
#include "tetromino_tools.hpp"
#include <vector>

/**
 * @brief a specialized wrapper of class @c AdjacentStates
 */
class MatrixAdjacentStates : public AdjacentStates<RunningBlockMatrix> {
public:
    MatrixAdjacentStates(): AdjacentStates<RunningBlockMatrix>() {}

    void cover_previous(BitMask& bit_mask) noexcept;

    void compare_map(BitMask& updated_recording_matrix) noexcept;
};

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
    const BitMask& get_updated_matrix() const noexcept;

    void update_matrix() noexcept;

    /**
     * @brief generate a new tetromino for the running block matrix
     */
    void generate_tetromino() noexcept;

    /**
     * @brief fix the tetromino when bottoming out
     */
    void fix_tetromino() noexcept;

    MatrixStateManager(const MatrixStateManager& ms) = delete;
    MatrixStateManager& operator==(const MatrixStateManager& ms) = delete;

private:
    // Singleton properties
    static MatrixStateManager* m_instance;
    static std::mutex m_mtx;

    // private constructor
    MatrixStateManager():
        m_running_matrix(),
        m_updated_matrix(BlockMatrixProperties::instance_read_only().x_size,
                         BlockMatrixProperties::instance_read_only().y_size) {}

    MatrixAdjacentStates m_running_matrix;
    BitMask m_updated_matrix;

    ~MatrixStateManager();
};

#endif //TETRIS_MATRIX_STATE_MANAGER_HPP
