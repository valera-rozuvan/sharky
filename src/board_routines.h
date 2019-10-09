#ifndef __BOARD_ROUTINES_H__
#define __BOARD_ROUTINES_H__

#define FileRank2SQ(f, r) ( (21 + (f) ) + ( 10 * (r) ))

extern unsigned char arr64to120[64];
extern unsigned char arr120to64[120];

void initBoardCoordConvArrays();
void printBoardCoordConvArrays();

#endif // __BOARD_ROUTINES_H__

