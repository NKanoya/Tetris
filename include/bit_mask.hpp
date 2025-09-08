//
// Created by pilip on 2025/9/8.
//

#ifndef TETRIS_BIT_MASK_HPP
#define TETRIS_BIT_MASK_HPP

#include <vector>
#include <bitset>

class BitMask {
    std::vector<uint32_t> bits; // 用32位整数存储位
    int width, height;

public:
    BitMask(int w, int h)
            : width(w), height(h),
              bits((w * h + 31) / 32, 0) {}

    void mark_dirty(int x, int y);

    bool is_dirty(int x, int y) const;

    inline void clear() {
        std::fill(bits.begin(), bits.end(), 0);
    }

    inline const std::vector<uint32_t>& get_data() const {
        return bits;
    }
};

#endif //TETRIS_BIT_MASK_HPP
