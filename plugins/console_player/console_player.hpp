//
// Created by pilip on 2025/9/13.
//

#ifndef TETRIS_console_player_HPP
#define TETRIS_console_player_HPP

#include "./../include/matrix_state_manager.hpp"

namespace ConsolePlayer {

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

    class ConsoleInput {

    };


}

#endif //TETRIS_console_player_HPP
