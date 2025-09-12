//
// Created by pilip on 2025/9/5.
//

#include "../../include/matrix.hpp"
#include "tetromino.hpp"

BlockMatrixProperties BlockMatrixProperties::m_instance;

BlockMatrixProperties::BlockMatrixProperties()  :
    x_size(22),
    y_size(10),
    x_buffer_size(2) {}

BlockMatrixProperties& BlockMatrixProperties::instance() noexcept {
    return m_instance;
}

const BlockMatrixProperties& BlockMatrixProperties::instance_read_only() noexcept {
    return m_instance;
}

BlockMatrix::BlockMatrix():
    // create the matrix array
    m_matrix(new TetrominoType[(bmatrix_prop.x_size) * bmatrix_prop.y_size])
{
    // initialize all the blocks
    for(int i = 0; i < bmatrix_prop.x_size * bmatrix_prop.y_size; i++) {
        m_matrix[i] = TetrominoType::empty;
    }
}

RunningBlockMatrix::RunningBlockMatrix(): BlockMatrix() {}

void RunningBlockMatrix::track_tetro() noexcept {
    // get previous position
    auto& previous_position = m_tetro -> get_previous_position();
    // clear original blocks
    for(auto& block: previous_position.blocks) {
        // TODO: remove the try-catch block by other strategies
        try {
            get_block(previous_position.axis.x + block.x,previous_position.axis.y + block.y) = TetrominoType::empty;
        } catch (const std::exception& e) {
            std::cerr << e.what();
        }

    }


    auto& axis = m_tetro -> get_current_position().axis;
    auto& shape = m_tetro -> get_current_position().blocks;

    for(auto& block: shape) {
        // TODO: remove the try-catch block by other strategies
        try {
            get_block(axis.x + block.x,axis.y + block.y) = m_tetro_type;
        } catch (const std::exception& e) {
            std::cerr << e.what();
        }

    }

    // TODO: print error info to log
}

void RunningBlockMatrix::bottom_out(std::shared_ptr<Tetromino>& new_tetro, TetrominoType tetro_type) {
    m_tetro = new_tetro;
    m_tetro_type = tetro_type;
}




