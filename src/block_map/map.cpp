//
// Created by pilip on 2025/9/5.
//

#include "../../include/map.hpp"

BlockMapProperties block_map_properties = {
        x_size: 10,
        y_size: 20
};

BlockMapProperties& bmap_prop = block_map_properties;

BlockMap::BlockMap():
    // create the map array
    m_map(new char[bmap_prop.x_size * bmap_prop.y_size])
{
    // initialize all the blocks
    for(int i = 0; i < bmap_prop.x_size * bmap_prop.y_size; i++) {
        m_map[i] = 0;
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