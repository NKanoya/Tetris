//
// Created by pilip on 2025/9/8.
//

#ifndef TETRIS_BIT_MASK_HPP
#define TETRIS_BIT_MASK_HPP

#include <vector>
#include <bitset>
#include <cstdint>

class BitMask {
    std::vector<uint32_t> bits; // 用32位整数存储位
    size_t width, height;

public:
    BitMask(size_t w, size_t h)
            : width(w), height(h),
              bits((w * h + 31) / 32, 0) {}

    void mark_dirty(size_t x, size_t y);

    bool is_dirty(size_t x, size_t y) const;

    inline void clear() {
        std::fill(bits.begin(), bits.end(), 0);
    }

    inline const std::vector<uint32_t>& get_data() const {
        return bits;
    }

    /**
     * @brief get the origin pointer of the source bit mask matrix.
     * @return ( <code>const void *</code> ) a constant pointer to the first element of the matrix.
     *
     * @note this function is intended for passing the matrix to the front end.
     */
     inline const void* get_source_bit_mask() const noexcept {
         return reinterpret_cast<const void*>(&(bits[0]));
     }

     inline size_t get_source_matrix_size() const noexcept {
         return bits.size() * sizeof(uint32_t);
     }
};

#endif //TETRIS_BIT_MASK_HPP
