#ifndef __BITBOARD_H__
#define __BITBOARD_H__

#define CLEAR_BIT(bBoard, bit) bBoard &= clrBitMask[bit]
#define SET_BIT(bBoard, bit) bBoard |= setBitMask[bit]

extern unsigned long long setBitMask[64];
extern unsigned long long clrBitMask[64];

void initBitMasks();

unsigned char count_1s(unsigned long long b);
unsigned char pop_1st_bit(unsigned long long *bb);

#endif // __BITBOARD_H__

