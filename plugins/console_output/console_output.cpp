#include "console_output.hpp"


/**
 * <p>implementations of functions of class @c BitMask
 *
 * <p>declared at @c matrix_state_manager.hpp
 */

namespace ConsoleOutput {
    static const char * const block_figure_ = "█▉";

    void ConsolePrinter::output_matrix(const RunningBlockMatrix& matrix) const noexcept {
        // clear previous output
        std::cout << "\033[2J\033[H";

        // traverse all blocks
        for(size_t x = *prop_buffer_size_ptr; x < *prop_x_axis_ptr; ++x) {
            for(size_t y = 0; y < *prop_y_axis_ptr; ++y) {
                // check the type of the block
                if( matrix.get_block(x,y) != TetrominoType::empty) {
                    std::cout << block_figure_;
                } else {
                    std::cout << "··";
                }
            }
            // enter the row
            std::cout << '\n';
        }

    }

    ConsolePrinter::ConsolePrinter() :
            prop_x_axis_ptr(&(BlockMatrixProperties::instance_read_only().x_size)),
            prop_y_axis_ptr(&(BlockMatrixProperties::instance_read_only().y_size)),
            prop_buffer_size_ptr(&(BlockMatrixProperties::instance_read_only().x_buffer_size)) {

    }

    void ConsolePrinter::output(const ConsolePrinter::ProcessData &data) const noexcept {
        output_matrix(data.matrix);
    }

}
