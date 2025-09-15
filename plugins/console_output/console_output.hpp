//
// Created by pilip on 2025/9/13.
//

#ifndef TETRIS_CONSOLE_OUTPUT_HPP
#define TETRIS_CONSOLE_OUTPUT_HPP

#include "./../include/matrix_state_manager.hpp"

namespace ConsoleOutput {

    class ConsolePrinter {
    public:
        using ProcessData = MatrixStateManager::ProcessData;

        void output(const ProcessData& data) const noexcept;

        void output_matrix(const RunningBlockMatrix& matrix) const noexcept;

        ConsolePrinter();

    private:
        const size_t* prop_x_axis_ptr;
        const size_t* prop_y_axis_ptr;
        const size_t* prop_buffer_size_ptr;
    };



}

#endif //TETRIS_CONSOLE_OUTPUT_HPP
