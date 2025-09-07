//
// Created by pilip on 2025/9/5.
//

#include "../../include/block_map.hpp"

BlockMapProperties BlockMapProperties::m_instance;

BlockMapProperties::BlockMapProperties()  :
    x_size(20),
    y_size(10),
    x_buffer_size(2) {}

BlockMapProperties& BlockMapProperties::instance() noexcept {
    return m_instance;
}

const BlockMapProperties& BlockMapProperties::instance_read_only() noexcept {
    return m_instance;
}

BlockMap::BlockMap():
    // create the map array
    m_map(new TetrominoType[bmap_prop.x_size * bmap_prop.y_size])
{
    // initialize all the blocks
    for(int i = 0; i < bmap_prop.x_size * bmap_prop.y_size; i++) {
        m_map[i] = TetrominoType::empty;
    }
}

MapState* MapState::m_instance = nullptr;
std::mutex MapState::m_mtx{};

MapState& MapState::getInstance() {
    if(m_instance == nullptr) {
        std::lock_guard<std::mutex> lock(m_mtx);
        if(m_instance == nullptr) {
            m_instance = new MapState();
        }
    }

    return *m_instance;
}

MapState::~MapState() {
    delete m_instance;
}