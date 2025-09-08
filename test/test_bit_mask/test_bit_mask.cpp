///
/// @file @c test/matrix/test_contianer.cpp
///

#include "../test_include.hpp"
#include "../../include/bit_mask.hpp"
#include <iostream>


namespace TetroTest {
    void test_bit_mask() {
        BitMask bt(10,10);

        for(int i = 0; i < 10; ++i) {
            bt.mark_dirty(i,i);
        }

        for(int i = 0; i < 10; ++i) {
            for(int j = 0; j < 10; ++j) {
                if(bt.is_dirty(i,j))
                    std::cout << '1';
                else std::cout << '0';
            }
            std::cout << std::endl;
        }

        bt.clear();  // 需要实现clear_dirty
        std::cout << '\n';

        for(int i = 0; i < 10; ++i) {
            for(int j = 0; j < 10; ++j) {
                if(bt.is_dirty(i,j))
                    std::cout << '1';
                else std::cout << '0';
            }
            std::cout << std::endl;
        }


    }
}
