///
/// @file @c test/matrix/test_console_output.cpp
///

#include "../test_include.hpp"
#include "../../include/adjacent_states.hpp"
#include "../../include/matrix_state_manager.hpp"
#include "../../plugins/console_output/console_output.hpp"


namespace TetroTest {
    void test_console_output() {
        auto& instance = MatrixStateManager::instance();

        for(int i = 0; i < 10; ++i) {
            auto data = instance.process_operation(Operation::Down);
            ConsoleOutput::ConsolePrinter printer;
            printer.output(data);
            std::cout << std::endl;
        }

    }
}
