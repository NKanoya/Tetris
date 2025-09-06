///
/// @file map.hpp
///

#ifndef TETRIS_MAP_HPP
#define TETRIS_MAP_HPP

#include <iostream>
#include <memory>

struct BlockMapProperties {
    size_t x_size;
    size_t y_size;
};

extern BlockMapProperties block_map_properties;

class BlockMap{
protected:
    std::unique_ptr<char[]> m_map;

public:
    BlockMap();

    inline char& get_block(size_t x, size_t y) const {
        // bound check
        if(x < block_map_properties.x_size && y < block_map_properties.y_size)
            return m_map[y * block_map_properties.x_size + x];

        // Throw out_of_range exception
        if(x > block_map_properties.x_size - 1)
            throw std::out_of_range("out of range: x-axis");
        else if (y > block_map_properties.y_size - 1)
            throw std::out_of_range("out of range: y-axis");
        return m_map[0];
    }
};

/*
 * @class @c MapState
 *
 * @brief A @b singleton class, recording blocks states in every ticks
 *
 * including current block map, block map at last tick, and the updated block map (signalling which blocks
 * have benn updated in this tick)
 */
class MapState {
private:
    // Singleton properties
    static MapState* m_instance;
    static std::mutex m_mtx;

    // private constructor
    MapState(): m_current_map(), m_last_map(), m_updated() {}

    BlockMap m_current_map;
    BlockMap m_last_map;
    BlockMap m_updated;

    // Currently moving Tetromino
    // std::unique_ptr<Tetromino> current_tetro;

public:

    // use the instance
    static MapState& getInstance();

    MapState(const MapState& ms) = delete;
    MapState& operator==(const MapState& ms) = delete;

    const BlockMap& get_current_map() const noexcept;
    const BlockMap& get_updated_map() const noexcept;

    update_map();


    ~MapState();
};

#endif //TETRIS_MAP_HPP
