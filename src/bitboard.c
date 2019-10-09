#include <stdio.h>

#include "defs.h"
#include "board_routines.h"

void printBitboard(unsigned long long bBoard) {
  char rankIter = 0;
  char fileIter = 0;
  unsigned char sq120 = 0;
  unsigned char sq64 = 0;

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

/*
 * Below 2 functions, and the constant array, are taken from:
 *   https://www.chessprogramming.org/Looking_for_Magics
 */
unsigned char count_1s(unsigned long long b) {
  unsigned char r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
}

const unsigned char BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

unsigned char pop_1st_bit(unsigned long long *bb) {
  unsigned long long b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));

  *bb &= (*bb - 1);

  return BitTable[(fold * 0x783a9b23) >> 26];
}

