//
// Created by pilip on 2025/9/10.
//

#ifndef TETRIS_TETROMINO_TOOLS_HPP
#define TETRIS_TETROMINO_TOOLS_HPP

#include <random>
#include "tetromino.hpp"

/**
 * @brief a pair to store current and upcoming tetrominoes
 */
class TetrominoesPair: protected AdjacentStates<std::shared_ptr<Tetromino>> {
public:

    /**
     * @brief Constructs a Tetrominoes pair with move semantics
     *
     * Tetromino objects are efficiently moved into the constructor using rvalue references,
     * avoiding unnecessary copying and enabling optimal resource transfer.
     *
     * @param tetro_current ( @c Tetromino&& ) - Current tetromino to be moved into the pair
     * @param tetro_upcoming ( @c Tetromino&& ) - Upcoming tetromino to be moved into the pair
     */
    TetrominoesPair(Tetromino&& tetro_current, Tetromino&& tetro_upcoming);

    /**
     * @brief get a modifiable non-constant reference of current tetromino
     *
     * the manager can track and operate this reference, to simulate a active tetromino
     *
     * @return @c Tetromino& : a non-constant reference of current tetromino
     */
    Tetromino& get_current() noexcept;

    /**
     * @brief Get if the current tetromino is bottoming out
     *
     * @return @c bool
     *
     * @callchain @c MatrixStateManager::is_bottom_out() : calls this ( @c const ) function to get if the state
     * of the tetromino in a @c const context
     *
     * @callchain @c Tetromino::is_bottom_out() : the target (forwarded) function
     */
    bool is_current_bottom_out() const noexcept;

    /**
     * @brief get the type of the next upcoming tetromino
     *
     * @return @c TetrominoType
     */
    TetrominoType get_upcoming_type() const noexcept;

    /**
     * @brief advances the tetromino sequence by moving the upcoming tetromino to current
     *        and setting a new upcoming tetromino
     *
     * operation sequence:
     * 1. destructs the current tetromino
     * 2. moves the upcoming tetromino to become the new current
     * 3. accepts the provided tetromino as the new upcoming tetromino
     *
     * this operation efficiently updates the current-upcoming pair using move semantics,
     * avoiding unnecessary copies of tetromino objects.
     *
     * @param new_upcoming ( @c Tetromino&& ) - New tetromino to set as the upcoming piece,
     *        will be moved from and left in valid but unspecified state
     * @return @c Tetromino& - Reference to the new current tetromino (previously upcoming)
     */
    Tetromino& replace_and_update(Tetromino&& new_upcoming) noexcept;

protected:
    using TetrominoPtr = std::shared_ptr<Tetromino>;
    // alias of the member to improve readability
    // the m_previous actually refers to the current tetromino pointer in this class
    // similarly m_current refers to the upcoming tetromino pointer in the class
    std::unique_ptr<TetrominoPtr>& m_current_tetro;
    std::unique_ptr<TetrominoPtr>& m_upcoming_tetro;
};

/**
 *
 */
class TetrominoGenerator {
public:
    /**
     * @brief a tool function to generate a new tetromino with random type
     * @param matrix_pair ( @c MatrixAdjacentStates* )
     * @return @c Tetromino a constructed tetromino
     */
    static Tetromino new_tetromino(MatrixAdjacentStates * matrix_pair) noexcept;

private:
    // random number engine
    static std::mt19937 rng;
    // the distribution
    static std::uniform_int_distribution<int> dist;

    /**
     * @brief get a random tetromino type by the random number generator
     * @return @c TetrominoType
     * @see used in function @c new_tetromino()
     */
    static TetrominoType get_random_type() noexcept;
};


#endif //TETRIS_TETROMINO_TOOLS_HPP
