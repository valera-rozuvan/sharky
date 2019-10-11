#ifndef __RANDOM_CONST_H__
#define __RANDOM_CONST_H__

// 12 * 64 => 12 different pieces, 64 squares where a piece can be
// 16 => different castling rights combinations (wQ 0/1, wK 0/1, bQ 0/1, bK 0/1)
// 16 => 16 possible enpassant squares (8 white and 8 black)
// 2 => side to move (white or black)
//
// So, we have:
//
// 12 * 64 + 16 + 16 + 2 = 802
extern unsigned long long RANDOM_CONST[1];

#endif // __RANDOM_CONST_H__

