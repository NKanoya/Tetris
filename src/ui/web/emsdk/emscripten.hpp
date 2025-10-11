//
// Created by pilip on 2025/9/20.
//

#ifndef TETRIS_EMSCRIPTEN_HPP
#define TETRIS_EMSCRIPTEN_HPP

#include "matrix_state_manager.hpp"

extern "C" {
    void output_in_JS(MatrixStateManager::ProcessData data);

    void add_operation(int op_num);
}


#endif //TETRIS_EMSCRIPTEN_HPP
