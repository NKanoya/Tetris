///
/// @file map.hpp
///

#ifndef TETRIS_BLOCK_MAP_HPP
#define TETRIS_BLOCK_MAP_HPP

enum class TetrominoType: unsigned char;
class Tetromino;

#include <iostream>
#include <memory>
#include "tetromino.hpp"
#include "rotate.hpp"

/**
 * @brief stores universal properties of block map
 *
 * @note @c BlockMapProperties follows @b Singleton Pattern
 * @note use @c instance() to get instance
 */
class BlockMapProperties {
private:
    // properties for singleton pattern
    static BlockMapProperties m_instance;
    static std::mutex m_mtx;

    // private constructor and destructor
    BlockMapProperties();
    ~BlockMapProperties();
public:
    // properties for the block map
    std::size_t x_size;    // vertical size
    std::size_t y_size;    // horizontal size
    std::size_t x_buffer_size;

    /**
     * @brief get the modifiable instance of the class @c BlockMapProperties
     *
     * @return ( @c BlockMapProperties& ): a reference to the singleton @c BlockMapProperties instance
     */
    static BlockMapProperties& instance() noexcept;

    /**
     * @brief get the read-only instance of the class @c BlockMapProperties
     *
     * @return ( <code>const BlockMapProperties&</code> ): a constant reference to the singleton @c BlockMapProperties instance
     */
    static const BlockMapProperties& instance_read_only() noexcept;

    // deleted copy constructor and assignment opertor
    BlockMapProperties(const BlockMapProperties& oth) = delete;
    BlockMapProperties& operator=(const BlockMapProperties& oth) = delete;
};

auto& bmap_prop = BlockMapProperties::instance_read_only();

class BlockMap{
protected:
    std::unique_ptr<TetrominoType[]> m_map;

public:
    BlockMap();

    inline TetrominoType& get_block(size_t x, size_t y) const;
};

class RunningBlockMap : public BlockMap {
protected:
    std::shared_ptr<Tetromino> m_tetro;
    TetrominoType m_tetro_type;
public:
    RunningBlockMap();
    void track_tetro() noexcept;
    void bottom_out();
};

inline TetrominoType &BlockMap::get_block(size_t x, size_t y) const {
    // bound check
    if(x < bmap_prop.x_size && y < bmap_prop.y_size)
        return m_map[y * bmap_prop.x_size + x];

    // Throw out_of_range exception
    if(x > bmap_prop.x_size - 1)
        throw std::out_of_range("out of range: x-axis");
    else if (y > bmap_prop.y_size - 1)
        throw std::out_of_range("out of range: y-axis");
    return m_map[0];
}

#endif //TETRIS_BLOCK_MAP_HPP
