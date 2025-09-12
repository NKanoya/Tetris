///
/// @file matrix.hpp
///

#ifndef TETRIS_MATRIX_HPP
#define TETRIS_MATRIX_HPP

enum class TetrominoType: unsigned char;
class Tetromino;

#include <iostream>
#include <memory>
#include "rotate.hpp"

/**
 * @brief stores universal properties of block matrix
 *
 * @note @c BlockMatrixProperties follows @b Singleton Pattern
 * @note use @c instance() to get instance
 */
class BlockMatrixProperties {
private:
    // properties for singleton pattern
    static BlockMatrixProperties m_instance;
    static std::mutex m_mtx;

    // private constructor and destructor
    BlockMatrixProperties();
    ~BlockMatrixProperties() = default;
public:
    // properties for the block matrix
    std::size_t x_size;    // vertical size
    std::size_t y_size;    // horizontal size
    std::size_t x_buffer_size;

    /**
     * @brief get the modifiable instance of the class @c BlockMatrixProperties
     *
     * @return ( @c BlockMatrixProperties& ): a reference to the singleton @c BlockMatrixProperties instance
     */
    static BlockMatrixProperties& instance() noexcept;

    /**
     * @brief get the read-only instance of the class @c BlockMatrixProperties
     *
     * @return ( <code>const BlockMatrixProperties&</code> ): a constant reference to the singleton @c BlockMatrixProperties instance
     */
    static const BlockMatrixProperties& instance_read_only() noexcept;

    // deleted copy constructor and assignment opertor
    BlockMatrixProperties(const BlockMatrixProperties& oth) = delete;
    BlockMatrixProperties& operator=(const BlockMatrixProperties& oth) = delete;
};

namespace {
    auto& bmatrix_prop = BlockMatrixProperties::instance_read_only();
}

class BlockMatrix {
protected:
    std::unique_ptr<TetrominoType[]> m_matrix;

public:
    BlockMatrix();

    inline TetrominoType& get_block(size_t x, size_t y) const;
};

class RunningBlockMatrix : public BlockMatrix {
protected:
    std::shared_ptr<Tetromino> m_tetro;
    TetrominoType m_tetro_type;
public:
    RunningBlockMatrix();
    void track_tetro() noexcept;
    void bottom_out(std::shared_ptr<Tetromino>& new_tetro, TetrominoType tetro_type);
};

inline TetrominoType &BlockMatrix::get_block(size_t x, size_t y) const {
    // bound check
    if(x < bmatrix_prop.x_size && y < bmatrix_prop.y_size)
        return m_matrix[y * bmatrix_prop.x_size + x];

    // Throw out_of_range exception
    if(x > bmatrix_prop.x_size - 1)
        throw std::out_of_range("out of range: x-axis");
    else if (y > bmatrix_prop.y_size - 1)
        throw std::out_of_range("out of range: y-axis");
    return m_matrix[0];
}

#endif //TETRIS_MATRIX_HPP
