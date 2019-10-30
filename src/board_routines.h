#ifndef __BOARD_ROUTINES_H__
#define __BOARD_ROUTINES_H__

#include "board.h"

#define FileRankTo120SQ(f, r) 21 + f + 10 * r

extern unsigned char board64to120[64];
extern unsigned char board120to64[120];

void printBoard64(unsigned long long bBoard);
void printBoard(BOARD *cBoard);

#define MAX_MOVE_STR_LENGTH 11

void chessMoveToStr(unsigned long long move, char fmtdMove[10]);
void printMoves(BOARD *cBoard);

void setupEmptyPosition(BOARD *cBoard);
void setupInitialPosition(BOARD *cBoard);

#endif // __BOARD_ROUTINES_H__
