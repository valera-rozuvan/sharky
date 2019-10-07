#include <stdio.h>

#include "defs.h"
#include "board_routines.h"

void printBitboard(U64 bBoard) {
  char rankIter = 0;
  char fileIter = 0;
  U8 sq120 = 0;
  U8 sq64 = 0;

  rankIter = RANK_8;
  do {
    fileIter = FILE_A;

    do {
      sq120 = FileRank2SQ(fileIter, rankIter);
      sq64 = arr120to64[sq120];

      if ((1ULL << sq64) & bBoard) {
        printf("X");
      } else {
        printf("-");
      }

      fileIter += 1;
    } while (fileIter <= FILE_H);

    printf("\n");
    rankIter -= 1;
  } while (rankIter >= RANK_1);

  printf("\n");
}

