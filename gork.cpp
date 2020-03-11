#include <stdio.h>
#include <stdint.h>
#include <array>
uint32_t gen_or_combine( uint32_t, size_t );
static uint32_t get_generic_mask( size_t );
int main() {
    uint32_t shamt = 0x1;
    uint32_t src1 = 0x11111110;
    static std::array<uint32_t, 5> masks = { 0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF };
    for(std::size_t i = 1, j = 0; i <= 16; i *= 2, j++) {
        if (shamt &  i) src1 |= ((src1 & masks.at(j)) <<  i) | ((src1 & (masks.at(j) ^ 0xFFFFFFFF) >>  i));
    }

    printf("%llX", src1);
}
// if (shamt &  1) src1 |= ((src1 & get_generic_mask(0)) <<  1) | ((src1 & (get_generic_mask(0) ^ 0xFFFFFFFF) >>  1));
// if (shamt &  2) src1 |= ((src1 & get_generic_mask(1)) <<  2) | ((src1 & (get_generic_mask(1) ^ 0xFFFFFFFF) >>  2));
// if (shamt &  4) src1 |= ((src1 & get_generic_mask(2)) <<  4) | ((src1 & (get_generic_mask(2) ^ 0xFFFFFFFF) >>  4));
// if (shamt &  8) src1 |= ((src1 & get_generic_mask(3)) <<  8) | ((src1 & (get_generic_mask(3) ^ 0xFFFFFFFF) >>  8));
// if (shamt & 16) src1 |= ((src1 & get_generic_mask(4)) <<  16) | ((src1 & (get_generic_mask(4) ^ 0xFFFFFFFF) >>  16));
// if (shamt &  1) src1 |= ((src1 & 0x5555555555555555LL) <<  1) |
//                         ((src1 & 0xAAAAAAAAAAAAAAAALL) >>  1);
// if (shamt &  2) src1 |= ((src1 & 0x3333333333333333LL) <<  2) |
//                         ((src1 & 0xCCCCCCCCCCCCCCCCLL) >>  2);
// if (shamt &  4) src1 |= ((src1 & 0x0F0F0F0F0F0F0F0FLL) <<  4) |
//                         ((src1 & 0xF0F0F0F0F0F0F0F0LL) >>  4);
// if (shamt &  8) src1 |= ((src1 & 0x00FF00FF00FF00FFLL) <<  8) |
//                         ((src1 & 0xFF00FF00FF00FF00LL) >>  8);
// if (shamt & 16) src1 |= ((src1 & 0x0000FFFF0000FFFFLL) << 16) |
//                         ((src1 & 0xFFFF0000FFFF0000LL) >> 16);
// if (shamt & 32) src1 |= ((src1 & 0x00000000FFFFFFFFLL) << 32) |
//                         ((src1 & 0xFFFFFFFF00000000LL) >> 32);
static uint32_t get_generic_mask( size_t index)
{
    static std::array<uint32_t, 5> masks = { 0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF };
    return masks.at( index);
}
