#include <iostream>
#include "test/test_include.hpp"
#include "matrix_state_manager.hpp"
#include "plugins/console_output/console_output.hpp"
#include <array>

int main() {
    try {
        TetroTest::test_console_output();
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
