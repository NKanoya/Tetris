///
/// @file @c src/tetromino.hpp
///



#ifndef TETRIS_TETROMINO_HPP
#define TETRIS_TETROMINO_HPP

class RunningBlockMap;

#include <array>
#include "block_map.hpp"
#include "rotate.hpp"        // for type BlockShape
#include "wall_kick.hpp"     // for enum class

enum class TetrominoType: unsigned char {
    empty,
    tetro_O,
    tetro_I,
    tetro_T,
    tetro_J,
    tetro_L,
    tetro_S,
    tetro_Z
};

/**
 * @brief Represents a tetromino, comprise of 4 blocks
 *
 * @ingroup @c RunningMap
 */
class Tetromino {
protected:

    TetrominoType m_type;

    /*
     * records 4 axises
     * describes 4 blocks' position related in its 4x4 frame grid
     * [0,0] is at the left-upper corner
     *
     * [0,0] [0,1] [0,2] [0,3]
     * [1,0] [1,1] [1,2] [1,3]
     * [2,0] [2,1] [2,2] [2,3]
     * [3,0] [3,1] [3,2] [3,3]
     */
    BlockShape m_blocks;

    // the absolute axis of its [0, 0] block within the block map
    Axis m_axis;

    // enum class RotateState
    // recorded to employ specific wall-kick displacement when the rotation is blocked
    RotateState m_rotate_state;

    // a weak pointer
    // points to the block map that possesses the tetromino
    RunningBlockMap * m_blockmap;

public:

    /**
     * construct a tetromino in a block map
     *
     * @ingroup a @c RunningMap class will store a tetromino with a @c std::unique_ptr
     *
     * @param type ( @c TetrominoType ):
     * @param axis ( <code>const Axis&</code> ): the initial position in the map
     * @param blockMap ( <code>const Axis&</code> ): a weak pointer to its block map
     */
    Tetromino(TetrominoType type, const Axis& axis, RunningBlockMap * blockMap) noexcept;

    // deleted copy constructor and assignment operator
    Tetromino(const Tetromino& oth) = delete;
    Tetromino& operator=(const Tetromino& oth) = delete;

    // default moving constructor and assignment operator
    Tetromino(Tetromino&& oth) = default;
    Tetromino& operator=(Tetromino&& oth) = default;

    /**
     * @brief lets the tetromino fall (move downwards) 1 block
     *
     * <p>if the falling movement is blocked (bottoming out), it will notify its owner block
     * to fix itself, and generate a new active tetromino.
     */
    void fall() noexcept;

    /**
     * @brief lets tetromino move 1 block leftwards
     *
     * <p>If the movement is blocked, the attempt will fail and the function will return.
     */
    void move_leftward() noexcept;

    /**
     * @brief lets tetromino move 1 block rightwards
     *
     * <p>If the movement is blocked, the attempt will fail and the function will return.
     */
    void move_rightward() noexcept;

    /**
     * @brief lets the tetromino rotate 90 degrees
     *
     * @param clockwise (@c bool , default: @c true ) the direction of rotation
     *
     * <p> The O, I, and other tetrominoes employ distinct rotation logic.
     *
     * @see the rotating logic is implemented in functions declared in @c rotate.hpp
     *
     * <p> if there's not enough room for the rotation, the function tries moves from the
     * wall kick table
     *
     * <p> if all wall-kick moves fail (blocked), the rotation fails and the function returns.
     *
     * @see the wall-kick logic is implemented in functions declared in @c wall_kick.hpp
     */
    void rotate(bool clockwise = true) noexcept;

    inline const BlockShape& get_shape() const noexcept {
        return m_blocks;
    }

    inline const Axis& get_axis() const noexcept {
        return m_axis;
    }

protected:

    /**
     * @brief correctly changes rotate state after rotation
     *
     * @param rotate_state ( @c BlockState& ): the block state to be changed
     * @param clockwise ( @c bool , default @c true ): the direction of rotation
     *
     * @see used in @c rotate()
     */
    static void change_rotate_state(RotateState& rotate_state, bool clockwise = true) noexcept;

    /**
     * @brief offsets a set of coordinates by a given displacement
     *
     * @param origin_axis ( @c Axis& ): the axis to offset
     * @param displacement ( <b>const Axis&</b> )
     *
     * @see used in @c rotate()
     */
    static void axis_displace(Axis& origin_axis, const Axis& displacement);

    /**
     * @brief employs the rotating operation
     *
     * <p>the operation includes changing coordinates of the blocks and switching rotation state
     *
     * <p>@b pure: the function won't conduct any checks or destination calculation, simply employing
     * the rotating operation based on given destination
     *
     * @param destination ( <b>const BlockShape&</b> ): the destination
     * @param clockwise ( @c bool , default @c true ): the rotating direction
     */
    void employ_rotation(const BlockShape& destination, bool clockwise = true) noexcept;

    /**
     * @brief checks if there's enough space for the wall kick operation
     *
     * check_space for the wall-kick displacement
     *
     * @param origin_dest ( <b>const BlockShape&</b> ): the original destination
     * @param wall_kick_disp ( <b>Axis</b> ): the wall-kick displacement
     * @return ( @c bool ): if the wall-kick operation have enough space
     */
     bool check_space_for_wall_kick(const BlockShape& origin_dest, const Axis& wall_kick_disp) const noexcept;
};

static constexpr BlockShape get_shape(TetrominoType type) noexcept;

#endif //TETRIS_TETROMINO_HPP
