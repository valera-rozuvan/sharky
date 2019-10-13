#ifndef __BITBOARD_H__
#define __BITBOARD_H__

#define CLEAR_BIT(bb, bit) bb &= clrBitMask[bit]
#define SET_BIT(bb, bit) bb |= setBitMask[bit]

extern unsigned long long setBitMask[64];
extern unsigned long long clrBitMask[64];

unsigned char count_1s(unsigned long long bb);
unsigned char pop_1st_bit(unsigned long long *bb);

#endif // __BITBOARD_H__
