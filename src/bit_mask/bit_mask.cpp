#include "../../include/bit_mask.hpp"


/**
 * <p>implementations of functions of class @c BitMask
 *
 * <p>declared at @c matrix_state_manager.hpp
 */
void BitMask::mark_dirty(size_t x, size_t y) {
    int index = y * width + x;
    bits[index / 32] |= (1u << (index % 32));
}

bool BitMask::is_dirty(size_t x, size_t y) const {
    int index = y * width + x;
    return (bits[index / 32] & (1u << (index % 32))) != 0;
}
