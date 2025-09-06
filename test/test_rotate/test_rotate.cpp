///
/// @file @c test/map/test_contianer.cpp
///

#include "../test_include.hpp"
#include "../../include/rotate.hpp"
#include <memory>    // for std::unique_ptr

namespace TetroTest {

    using TetroStyles = std::array<BlockShape, 4>;
    static void print_shape(const TetroStyles& arr);
    static void test_print_shape();
    static void test_rotate_I();
    static void test_rotate_normal(const char* const name, BlockShape begin_style);

    void test_rotate() {
        test_print_shape();

        // test rotation of tetro I
        test_rotate_I();

        // test rotation of tetro T
        test_rotate_normal("tetro T", {{{1,1},{0, 1}, {1, 0}, {1, 2}}});

        // test rotation of tetro J
        test_rotate_normal("tetro J", {{{1,1},{0, 0}, {1, 0}, {1, 2}}});

        // test rotation of tetro L
        test_rotate_normal("tetro L", {{{1,1},{0, 2}, {1, 0}, {1, 2}}});

        // test rotation of tetro S
        test_rotate_normal("tetro S", {{{1,1},{0, 1}, {0, 2}, {1, 0}}});

        // test rotation of tetro Z
        test_rotate_normal("tetro Z", {{{1,1},{0, 0}, {0, 1}, {1, 2}}});

    }



    static void print_shape(const TetroStyles& arr) {
        char blocks_pixels_sets[4][4][4] = {};
        // traverse 4 block shape
        for(int i = 0; i < 4; ++i) {
            // fill pixels in 4 blocks
            auto block_axis = arr[i];
            auto block_px = blocks_pixels_sets[i];

            for(auto& axis: block_axis) {
                block_px[axis.x][axis.y] = 1;
            }
        }

        // traverse 4 lines
        for(int i = 0; i < 4; ++i) {
            // traverse 4 blocks
            for(int j = 0; j < 4; ++j) {
                // traverse 4 pixels
                for(int k = 0; k < 4; ++k) {
                    if(blocks_pixels_sets[j][i][k] != 0) {
                        std::cout << "█▉";
                    } else {
                        std::cout << "··";
                    }
                }
                std::cout << "  ";

            }
            std::cout << '\n';
        }
        std::cout << std::endl;
    }


    static void test_print_shape() {
        printf("=======================================================\n\n");
        std::cout << "Test static function print_shape():" << '\n';
        TetroStyles sample = {{
                                      {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}},
                                      {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}},
                                      {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}},
                                      {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}}
                              }};

        print_shape(sample);
        printf("=======================================================");
        std::cout << std::endl;
    }

    TetroStyles styles = {};

    static void test_rotate_I() {
        printf("=======================================================\n\n");
        std::cout << "Test rotate function for tetro I (clockwise):" << '\n';

        styles = {};
        styles[0] = {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}};
        for(int i = 0; i < 3; ++i) {
            eval_rotate_dest_I(styles[i],styles[i + 1]);
        }
        print_shape(styles);

        // test counterclockwise rotation

        std::cout << "Test rotate function for tetro I (counterclockwise):" << '\n';

        styles = {};
        styles[0] = {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}};
        for(int i = 0; i < 3; ++i) {
            eval_rotate_dest_I(styles[i],styles[i + 1], false);
        }
        print_shape(styles);
        printf("=======================================================");
        std::cout << std::endl;
    }

    static void test_rotate_normal(const char* const name, BlockShape begin_style) {
        printf("=======================================================\n\n");
        printf("Test rotate function for %s (clockwise):\n", name);
        styles = {};
        styles[0] = begin_style;
        for(int i = 0; i < 3; ++i) {
            eval_rotate_dest_normal(styles[i],styles[i + 1]);
        }
        print_shape(styles);

        printf("Test rotate function for %s (counterclockwise):\n", name);
        styles = {};
        styles[0] = begin_style;
        for(int i = 0; i < 3; ++i) {
            eval_rotate_dest_normal(styles[i],styles[i + 1],false);
        }
        print_shape(styles);

        printf("=======================================================");
        std::cout << std::endl;
    }
}



