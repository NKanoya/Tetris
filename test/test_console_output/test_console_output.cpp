///
/// @file @c test/matrix/test_console_output.cpp
///

#include "../test_include.hpp"
#include "../../include/adjacent_states.hpp"
#include "../../include/matrix_state_manager.hpp"
#include "../../plugins/console_output/console_output.hpp"


namespace TetroTest {

    void operate(Operation op){
        static auto& instance = MatrixStateManager::instance();
        auto data = instance.process_operation(op);
        ConsoleOutput::ConsolePrinter printer;
        printer.output(data);
        std::cout << std::endl;
    }

    void test_console_output() {
        operate(Operation::Down);
        operate(Operation::Left);
        operate(Operation::Right);
        operate(Operation::Right);
        operate(Operation::RotateCW);
        operate(Operation::RotateCW);
        operate(Operation::Down);
        operate(Operation::RotateCCW);
        operate(Operation::Drop);
    }
}
