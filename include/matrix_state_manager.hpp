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
 *
 * two matrix respectively records the current state and the previous state of the block
 * matrix
 *
 * @ingroup class @c MatrixStateManager
 */
class MatrixAdjacentStates : public AdjacentStates<RunningBlockMatrix> {
public:

    /**
     * @brief Constructs a wrapper of adjacent states of a matrix
     */
    MatrixAdjacentStates(): AdjacentStates<RunningBlockMatrix>() {}

    /**
     * @brief Applies incremental updates from the current state to the previous state using a bitmask
     *
     * @param bit_mask ( <code>const BitMask&</code> ) : Bitmask identifying the modified pixels between previous and current states.
     *
     * Optimizes performance by avoiding full matrix copies and only transferring modified pixels.
     */
    void cover_previous(const BitMask& bit_mask) noexcept;

    /**
     * @brief Synchronizes matrix states and updates the modification bitmask.
     *
     * <p>This function performs a complete state synchronization cycle:
     * <ol>
     *   <li> Applies current modifications to the previous state</li>
     *   <li> Updates the current state tracking</li>
     *   <li> Resets and rebuilds the modification bitmask from scratch</li>
     * </ol>
     *
     * @param recording_bitmask ( @c BitMask& ): Reference to the bitmask that will be repopulated with
     *                          all currently differing pixels between current and previous states.
     *
     * @note The bitmask is completely cleared and rebuilt, making this operation suitable for
     *       full state resynchronization rather than incremental updates.
     */
    void reload_modifies_bitmask(BitMask& recording_bitmask) noexcept;
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

    /**
     * @brief gets the bitmask signing all the updated pixels
     *
     * @return @c BitMask& : the constant reference of the bitmap
     *
     * @see to update the bitmap, call @c update_modifies_bitmask()
     */
    const BitMask& get_modifies_bitmask() const noexcept;

    /**
     * @brief updates the bitmask indicating modified blocks
     *
     * The bitmask uses each bit to represent whether the corresponding block
     * has been updated (1) or remains unchanged (0).
     *
     * @return @c BitMask& : the constant reference of the bitmap
     *
     * @see to get the matrix, call @c get_modifies_bitmask()
     */
    void update_modifies_bitmask() noexcept;

    /**
     * @brief Advances the tetromino queue by moving the upcoming tetromino to current
     *        and generate a new tetromino in the upcoming slot
     *
     * @return @c Tetromino& : Reference to the new current tetromino (previously upcoming)
     */
    Tetromino& new_tetromino() noexcept;

    /**
     * @brief check if the current tetromino is bottoming out
     *
     * @return @c bool
     *
     * @callchain this function -> @c TetrominoesPair::is_current_bottom_out() ->
     * @c Tetromino::is_bottom_out
     */
    bool is_current_tetro_bottom_out() const noexcept;

    // deleted copy constructor and assignment operator
    MatrixStateManager(const MatrixStateManager& ms) = delete;
    MatrixStateManager& operator==(const MatrixStateManager& ms) = delete;

private:
    // Singleton properties
    static MatrixStateManager* m_instance;
    // mutex
    static std::mutex m_mtx;
    // running matrix: including both its current and previous states
    MatrixAdjacentStates m_running_matrix;
    // the bit mask of updated pixels
    BitMask m_modifies_bitmask;
    // the current and upcoming tetrominoes
    TetrominoesPair m_tetro_queue;

    // private constructor
    MatrixStateManager();

    ~MatrixStateManager();
};

#endif //TETRIS_MATRIX_STATE_MANAGER_HPP
