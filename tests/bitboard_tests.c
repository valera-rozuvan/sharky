#include <stdlib.h>
#include <stdio.h>

#include "../src/defs.h"
#include "../src/board_routines.h"
#include "../src/bitboard.h"

void setClrTests()
{
  unsigned long long bBoard = 0ULL;

  const unsigned char squares[32] = {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,

    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
  };
  const char *squaresStr[32] = {
    "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
    "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",

    "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
    "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"
  };

  unsigned char idx = 0;

  for (idx = 0; idx < 32; idx += 1) {
    SET_BIT(bBoard, board120to64[squares[idx]]);
    CLEAR_BIT(bBoard, board120to64[squares[idx]]);

    if (bBoard != 0ULL) {
      printf("Single run: set & clear %s fail!\n\n", squaresStr[idx]);
      exit(0);
    }
  }

  for (idx = 0; idx < 32; idx += 1) {
    SET_BIT(bBoard, board120to64[squares[idx]]);
    SET_BIT(bBoard, board120to64[squares[idx]]);

    CLEAR_BIT(bBoard, board120to64[squares[idx]]);

    if (bBoard != 0ULL) {
      printf("Double SET_BIT run: set & clear %s fail!\n\n", squaresStr[idx]);
      exit(0);
    }
  }

  for (idx = 0; idx < 32; idx += 1) {
    SET_BIT(bBoard, board120to64[squares[idx]]);

    CLEAR_BIT(bBoard, board120to64[squares[idx]]);
    CLEAR_BIT(bBoard, board120to64[squares[idx]]);

    if (bBoard != 0ULL) {
      printf("Double CLEAR_BIT run: set & clear %s fail!\n\n", squaresStr[idx]);
      exit(0);
    }
  }
}

void countTests()
{
  unsigned long long bBoard = 0ULL;
  unsigned char bitCount = count_1s(bBoard);

  if (bitCount != 0) {
    printf("bitCount != 0; bitCount = %hhu\n\n", bitCount);
  }

  bBoard |= (1ULL << board120to64[D2]);
  bBoard |= (1ULL << board120to64[G7]);
  bBoard |= (1ULL << board120to64[A5]);
  bBoard |= (1ULL << board120to64[E2]);
  bBoard |= (1ULL << board120to64[H3]);
  bBoard |= (1ULL << board120to64[B8]);
  bBoard |= (1ULL << board120to64[G1]);

  bitCount = count_1s(bBoard);

  if (bitCount != 7) {
    printf("bitCount != 7; bitCount = %hhu\n\n", bitCount);
  }

  bBoard = 18446744073709551615ULL; // (2^64) - 1 = 8446744073709551615
  bitCount = count_1s(bBoard);

  if (bitCount != 64) {
    printf("bitCount != 64; bitCount = %hhu\n\n", bitCount);
  }
}

void popTests()
{
  unsigned long long bBoard = 0ULL;
  unsigned char poppedBit = 0;

  bBoard |= (1ULL << board120to64[D2]);
  bBoard |= (1ULL << board120to64[G7]);
  bBoard |= (1ULL << board120to64[A5]);
  bBoard |= (1ULL << board120to64[E2]);
  bBoard |= (1ULL << board120to64[H3]);
  bBoard |= (1ULL << board120to64[B8]);
  bBoard |= (1ULL << board120to64[G1]);

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[G1]) {
    printf("poppedBit != board120to64[G1]; poppedBit = %hhu\n\n", poppedBit);
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[D2]) {
    printf("poppedBit != board120to64[D2]; poppedBit = %hhu\n\n", poppedBit);
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[E2]) {
    printf("poppedBit != board120to64[E2]; poppedBit = %hhu\n\n", poppedBit);
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[H3]) {
    printf("poppedBit != board120to64[H3]; poppedBit = %hhu\n\n", poppedBit);
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[A5]) {
    printf("poppedBit != board120to64[A5]; poppedBit = %hhu\n\n", poppedBit);
  }
}

void bitboard_tests()
{
  setClrTests();
  countTests();
  popTests();
}
