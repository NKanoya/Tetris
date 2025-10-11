///
/// @file @c test/matrix/test_contianer.cpp
///

#include "../test_include.hpp"
#include "adjacent_states.hpp"


namespace TetroTest {
    void test_double_buffer() {
        std::cout << "Initialize a AdjacentStates object with value 'Text 1'\n";
        AdjacentStates<std::string> db("Text 1");
        std::cout << "Print current: 'Text 1'\n";
        std::cout << db.read_current() << '\n';

        std::cout << "Update current with value: 'Text 2':\n";
        auto& current_1 = db.update_current([](std::string& str){
            str = "Text 2";
        });
        std::cout << "Print 'Text 2' with read_current():\n";
        std::cout << current_1 << '\n';
        std::cout << "Print previous text with read_previous():\n";
        std::cout << db.read_previous() << std::endl;

        std::cout << "Update current with value: 'Text 3':\n";
        auto& current_2 = db.update_current([](std::string& str){
            str = "Text 3";
        });
        std::cout << "Print 'Text 3' with read_current():\n";
        std::cout << current_2 << '\n';
        std::cout << "Print previous text with read_previous():\n";
        std::cout << db.read_previous() << std::endl;
    }
}
