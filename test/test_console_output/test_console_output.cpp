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
        auto data = instance.process_operation(Operation::Down);
        ConsoleOutput::ConsolePrinter printer;

        printer.output(data);
    }
}
