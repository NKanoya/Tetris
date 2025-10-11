#include <iostream>
#include "test/test_include.hpp"
#include "include/matrix_state_manager.hpp"
#include "include/time_event_system.hpp"
#include "src/ui/web/emsdk/emscripten.hpp"
#include <chrono>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>


#ifndef TETRIS_JS_OUTPUT

int main() {
    MatrixStateManager& manager = MatrixStateManager::instance();

    constexpr int fps = 15;

    OperationQueue op_q;

    auto command_func = [&op_q]() -> OperationQueue& {
        return op_q;
    };

    auto process_func = [&manager](Operation op) -> MatrixStateManager::ProcessData {
        return manager.process_operation(op);
    };

    TickCircle<fps> circle(std::chrono::milliseconds(1000),
                          command_func,
                          process_func,
                          output_in_JS);




    circle.game_loop();
    return 0;
}
#endif




#ifdef TETRIS_JS_OUTPUT

constexpr int fps = 15;

MatrixStateManager* manager;

OperationQueue* op_q;

static TickCircle<fps>* circle_ptr = nullptr;

void game_loop_function() {
    try{
        if (circle_ptr) {
            circle_ptr->game_loop();
        }
    } catch (std::exception& e){
        printf("%s",e.what());
    }
}

OperationQueue& command_func() {
    op_q = new OperationQueue();
    return *op_q;
}

MatrixStateManager::ProcessData process_func(Operation op) {
    manager = &MatrixStateManager::instance();
    return manager -> process_operation(op);
};


extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void JS_process_loop() {
        emscripten_set_main_loop(game_loop_function, fps, true);
    }
}



int main(){
    circle_ptr = new TickCircle<fps>(
            std::chrono::milliseconds(1000),
            command_func,
            process_func,
            output_in_JS
    );

    circle_ptr->init_loop();

    return 0;
}


#endif