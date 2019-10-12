#ifndef __BOARD_ROUTINES_H__
#define __BOARD_ROUTINES_H__

#define FileRank2SQ(f, r) 21 + f + 10 * r

extern unsigned char board64to120[64];
extern unsigned char board120to64[120];

void printBoard64(unsigned long long bBoard);

#endif // __BOARD_ROUTINES_H__

