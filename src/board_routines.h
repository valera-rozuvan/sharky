#ifndef __BOARD_ROUTINES_H__
#define __BOARD_ROUTINES_H__

#define FileRank2SQ(f, r) ( (21 + (f) ) + ( 10 * (r) ))

extern U8 arr64to120[64];
extern U8 arr120to64[120];

void initBoardCoordConvArrays();
void printBoardCoordConvArrays();

#endif // __BOARD_ROUTINES_H__

