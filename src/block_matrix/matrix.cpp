//
// Created by pilip on 2025/9/5.
//

#include "../../include/matrix.hpp"
#include "tetromino.hpp"
#include <algorithm>

BlockMatrixProperties BlockMatrixProperties::m_instance;

BlockMatrixProperties::BlockMatrixProperties()  :
    x_size(22),
    y_size(10),
    x_buffer_size(2),
    check_failed_signal(114514) {}

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
    for(size_t i = 0; i < bmatrix_prop.x_size * bmatrix_prop.y_size; i++) {
        m_matrix[i] = TetrominoType::empty;
    }
}

RunningBlockMatrix::RunningBlockMatrix():
    BlockMatrix(),
    m_tetro_type(m_tetro->get_type()),
    m_completed_rows_number(0),
    m_over_buffer(false),
    m_completed_rows(4) {}

size_t RunningBlockMatrix::track_tetro() noexcept {
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

    // traverse the blocks and shape
    auto& axis = m_tetro -> get_current_position().axis;
    auto& shape = m_tetro -> get_current_position().blocks;

    // update the blocks of destination
    for(auto& block: shape) {
        // TODO: remove the try-catch block by other strategies
        try {
            get_block(axis.x + block.x,axis.y + block.y) = m_tetro_type;
        } catch (const std::exception& e) {
            std::cerr << e.what();
        }

    }

    if(m_tetro -> is_bottom_out()) {
        // check if the game is lost
        for(auto& block: shape) {
            if(axis.x + block.x < BlockMatrixProperties::instance_read_only().x_buffer_size){
                // the game is lost
                m_over_buffer = true;
                // return a failed signal value
                return BlockMatrixProperties::instance_read_only().check_failed_signal;
            }
        }

        // check if there is completed rows
        check_completed_rows(axis, shape);
        if(m_completed_rows_number != 0) {
            auto completed_lines = clear_completed_rows();
            return completed_lines;
        }
    }

    return 0;
}

void RunningBlockMatrix::check_completed_rows(const Axis& axis, const BlockShape& shape) const noexcept {
    // sign the updated rows
    bool is_row_updated[4] = {false,false,false,false};
    for(auto& block: shape) {
        is_row_updated[block.x] = true;     // if there is any updates in the row
        // its index will be signed true
    }

    // check if the row is completed
    bool is_row_completed[4] = {false,false,false,false};
    // a dynamic sign, indicating if there is found any empty block in this row
    bool find_empty = false;
    for(int i = 0; i < 4; ++i) {
        if (is_row_updated[i]) {
            // if the row is updated, then check if it is completed

            // traverse all column
            for (int j = 0; j < BlockMatrixProperties::instance_read_only().y_size; ++j) {
                try {    // TODO: remove the try-catch block by other strategies
                    // check if there is  blocks
                    if (get_block(axis.x + i, j) == TetrominoType::empty) {
                        find_empty = true;    // find an empty block
                        break;                // end the check of this row
                    }
                } catch (const std::exception &e) {
                    std::cerr << e.what();
                }
            }

            if (!find_empty) {                   // if the whole root does not find any empty blocks
                is_row_completed[i] = true;     // set the sign `is_row_completed` of the row to true
            }

        }
        // if the row isn't updated, just skip it
    }

    m_completed_rows_number = 0;
    for(int i = 0; i < 4; ++i) {
        m_completed_rows[m_completed_rows_number] = axis.x + i;
        ++m_completed_rows_number;
    }
}

size_t RunningBlockMatrix::clear_completed_rows() noexcept {
    size_t completed_number = m_completed_rows_number;
    m_completed_rows_number = 0;      // clear the number

    // the row pointer
    using RowPtr = TetrominoType (*)[BlockMatrixProperties::instance_read_only().y_size];
    auto height = BlockMatrixProperties::instance_read_only().x_size;
    bool rows_to_clear[height];
    std::fill(rows_to_clear, rows_to_clear + height, false);

    for(size_t i = 0; i < completed_number; ++i) {
        // get the indexes of the rows to be cleared
        auto row_number = m_completed_rows[i];
        // sign their index by true
        rows_to_clear[row_number] = true;
    }

    size_t write_row = height - 1; // 从最底部开始写
    size_t width = BlockMatrixProperties::instance_read_only().y_size;

    // scan from the bottom
    for (ptrdiff_t read_row = height - 1; read_row >= 0; --read_row) {
        if (!rows_to_clear[read_row]) {
            // copy the whole row
            for (size_t col = 0; col < width; ++col) {
                get_block(write_row,col) = get_block(read_row,col);
            }
            --write_row;
        }
    }

    // clear all rows at the top of the matrix
    for (int row = 0; row <= write_row; ++row) {
        for (size_t col = 0; col < width; ++col) {
            get_block(row,col) = TetrominoType::empty;
        }
    }

    return completed_number;
}







