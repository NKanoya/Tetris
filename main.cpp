#include <iostream>
#include "test/test_include.hpp"
#include "include/matrix_state_manager.hpp"
#include "plugins/console_player/console_player.hpp"
#include "include/time_event_system.hpp"
#include <chrono>

int main() {
    ConsolePlayer::ConsoleScanner sc;
    ConsolePlayer::ConsolePrinter pr;
    MatrixStateManager& manager = MatrixStateManager::instance();

    auto command_func = [&sc]() -> Operation {
        return sc.input();
    };

    auto process_func = [&manager](Operation op) -> MatrixStateManager::ProcessData {
        return manager.process_operation(op);
    };

    auto render_func = [&pr](const MatrixStateManager::ProcessData data) {
        pr.output(data);
    };

    TickCircle<30> circle(std::chrono::milliseconds(1000),
                          command_func,
                          process_func,
                          render_func);
    circle.game_loop();
    return 0;
}
