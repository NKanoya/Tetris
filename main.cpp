#include <iostream>
#include "test/test_include.hpp"
#include <array>

int main() {
    try {
        TetroTest::test_tetromino_tools();
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    return 0;
}
