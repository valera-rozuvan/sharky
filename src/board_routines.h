#ifndef __BOARD_ROUTINES_H__
#define __BOARD_ROUTINES_H__

#include "board.h"

#define FileRankTo120SQ(f, r) 21 + f + 10 * r

extern unsigned char board64to120[64];
extern unsigned char board120to64[120];
extern unsigned char board120toFile[120];

void printBoard(BOARD *cBoard);

// 5 + 1 = 6 // max move length + 1 (the 1 is `\0` char - C string termination character)
#define MAX_MOVE_STR_LENGTH 6

void chessMoveToStr(unsigned long long move, char fmtdMove[MAX_MOVE_STR_LENGTH]);
void printBestMove(BOARD *cBoard);
void printMoves(BOARD *cBoard);

void setupEmptyPosition(BOARD *cBoard);
void setupInitialPosition(BOARD *cBoard);

unsigned char checkDrawByRepetition(BOARD *cBoard);

#endif // __BOARD_ROUTINES_H__
