#include <iostream>
#include "test/test_include.hpp"
#include "matrix_state_manager.hpp"
#include "plugins/console_player/console_player.hpp"
#include <array>

int main() {
    try {
        TetroTest::test_console_input();
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
