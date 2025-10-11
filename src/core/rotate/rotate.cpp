///
/// @file @c src/rotate/rotate.cpp
///

#include "rotate.hpp"



void eval_rotate_dest_I(const BlockShape& source, BlockShape& destination, bool clockwise) {
    if(&source == &destination){
        // unsupported operation
        // TODO: print warning info to log
        return;
    }

    // rotate clockwise
    if(clockwise) {
        for(int i = 0; i < 4; ++i) {
            destination[i].x = source[i].y;
            destination[i].y = 3 - source[i].x;
        }
    }
    // rotate counterclockwise
    else {
        for(int i = 0; i < 4; ++i) {
            destination[i].x = 3 - source[i].y;
            destination[i].y = source[i].x;
        }
    }
}

void eval_rotate_dest_normal(const BlockShape& source, BlockShape& destination, bool clockwise) {
    if(&source == &destination){
        // unsupported operation
        // TODO: print warning info to log
        return;
    }

    // rotate clockwise
    if(clockwise) {
        for(int i = 0; i < 4; ++i) {
            destination[i].x = source[i].y;
            destination[i].y = 2 - source[i].x;
        }
    }
    // rotate counterclockwise
    else {
        for(int i = 0; i < 4; ++i) {
            destination[i].x = 2 - source[i].y;
            destination[i].y = source[i].x;
        }
    }
}

