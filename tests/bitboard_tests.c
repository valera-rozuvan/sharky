#include <stdlib.h>
#include <stdio.h>

#include "../src/defs.h"
#include "../src/board_routines.h"
#include "../src/bitboard.h"

#include "tests.h"

/* ------------------------------ */
/*       char type section        */
/* ------------------------------ */

void assertBitIsZero_uc(unsigned char uc, unsigned char bit)
{
  if (CHECK_BIT(uc, bit)) {
    printf("macroTests: assertBitIsZero_uc fail! uc = %hhu, bit = %hhu\n\n", uc, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_uc(unsigned char uc, unsigned char bit)
{
  if (!CHECK_BIT(uc, bit)) {
    printf("macroTests: assertBitIsOne_uc fail! uc = %hhu, bit = %hhu\n\n", uc, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsZero_sc(char sc, unsigned char bit)
{
  if (CHECK_BIT(sc, bit)) {
    printf("macroTests: assertBitIsZero_sc fail! sc = %hhi, bit = %hhu\n\n", sc, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_sc(char sc, unsigned char bit)
{
  if (!CHECK_BIT(sc, bit)) {
    printf("macroTests: assertBitIsOne_sc fail! sc = %hhi, bit = %hhu\n\n", sc, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

/* ------------------------------ */
/*       short type section       */
/* ------------------------------ */

void assertBitIsZero_us(unsigned short us, unsigned char bit)
{
  if (CHECK_BIT(us, bit)) {
    printf("macroTests: assertBitIsZero_us fail! us = %hu, bit = %hhu\n\n", us, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_us(unsigned short us, unsigned char bit)
{
  if (!CHECK_BIT(us, bit)) {
    printf("macroTests: assertBitIsOne_us fail! us = %hu, bit = %hhu\n\n", us, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsZero_ss(short ss, unsigned char bit)
{
  if (CHECK_BIT(ss, bit)) {
    printf("macroTests: assertBitIsZero_ss fail! ss = %hi, bit = %hhu\n\n", ss, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_ss(short ss, unsigned char bit)
{
  if (!CHECK_BIT(ss, bit)) {
    printf("macroTests: assertBitIsOne_ss fail! ss = %hi, bit = %hhu\n\n", ss, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

/* ------------------------------ */
/*       long type section        */
/* ------------------------------ */

void assertBitIsZero_ul(unsigned long ul, unsigned char bit)
{
  if (CHECK_BIT(ul, bit)) {
    printf("macroTests: assertBitIsZero_ul fail! ul = %lu, bit = %hhu\n\n", ul, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_ul(unsigned long ul, unsigned char bit)
{
  if (!CHECK_BIT(ul, bit)) {
    printf("macroTests: assertBitIsOne_ul fail! ul = %lu, bit = %hhu\n\n", ul, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsZero_sl(long sl, unsigned char bit)
{
  if (CHECK_BIT(sl, bit)) {
    printf("macroTests: assertBitIsZero_sl fail! sl = %li, bit = %hhu\n\n", sl, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_sl(long sl, unsigned char bit)
{
  if (!CHECK_BIT(sl, bit)) {
    printf("macroTests: assertBitIsOne_sl fail! sl = %li, bit = %hhu\n\n", sl, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

/* ------------------------------ */
/*     long long type section     */
/* ------------------------------ */

void assertBitIsZero_ull(unsigned long long ull, unsigned char bit)
{
  if (CHECK_BIT(ull, bit)) {
    printf("macroTests: assertBitIsZero_ull fail! ull = %llu, bit = %hhu\n\n", ull, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_ull(unsigned long long ull, unsigned char bit)
{
  if (!CHECK_BIT(ull, bit)) {
    printf("macroTests: assertBitIsOne_ull fail! ull = %llu, bit = %hhu\n\n", ull, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsZero_sll(long long sll, unsigned char bit)
{
  if (CHECK_BIT(sll, bit)) {
    printf("macroTests: assertBitIsZero_sll fail! sll = %lli, bit = %hhu\n\n", sll, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void assertBitIsOne_sll(long long sll, unsigned char bit)
{
  if (!CHECK_BIT(sll, bit)) {
    printf("macroTests: assertBitIsOne_sll fail! sll = %lli, bit = %hhu\n\n", sll, bit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

/* ------------------------------ */

void macroTestsChar()
{
  unsigned char idx = 0;

  unsigned char uc = 0;
  char sc = 0;

  for (idx = 0; idx < 8; idx += 1) {
    assertBitIsZero_uc(uc, idx);
    SET_BIT(uc, idx);
    assertBitIsOne_uc(uc, idx);
    CLEAR_BIT(uc, idx);
    assertBitIsZero_uc(uc, idx);
  }

  for (idx = 0; idx < 8; idx += 1) {
    assertBitIsZero_sc(sc, idx);
    SET_BIT(sc, idx);
    assertBitIsOne_sc(sc, idx);
    CLEAR_BIT(sc, idx);
    assertBitIsZero_sc(sc, idx);
  }
}

void macroTestsShort()
{
  unsigned char idx = 0;

  unsigned short us = 0;
  short ss = 0;

  for (idx = 0; idx < 16; idx += 1) {
    assertBitIsZero_us(us, idx);
    SET_BIT(us, idx);
    assertBitIsOne_us(us, idx);
    CLEAR_BIT(us, idx);
    assertBitIsZero_us(us, idx);
  }

  for (idx = 0; idx < 16; idx += 1) {
    assertBitIsZero_ss(ss, idx);
    SET_BIT(ss, idx);
    assertBitIsOne_ss(ss, idx);
    CLEAR_BIT(ss, idx);
    assertBitIsZero_ss(ss, idx);
  }
}

void macroTestsLong()
{
  unsigned char idx = 0;

  unsigned long ul = 0;
  long sl = 0;

  for (idx = 0; idx < 32; idx += 1) {
    assertBitIsZero_ul(ul, idx);
    SET_BIT(ul, idx);
    assertBitIsOne_ul(ul, idx);
    CLEAR_BIT(ul, idx);
    assertBitIsZero_ul(ul, idx);
  }

  for (idx = 0; idx < 32; idx += 1) {
    assertBitIsZero_sl(sl, idx);
    SET_BIT(sl, idx);
    assertBitIsOne_sl(sl, idx);
    CLEAR_BIT(sl, idx);
    assertBitIsZero_sl(sl, idx);
  }
}

void macroTestsLongLong()
{
  unsigned char idx = 0;

  unsigned long long ull = 0;
  long long sll = 0;

  for (idx = 0; idx < 64; idx += 1) {
    assertBitIsZero_ull(ull, idx);
    SET_BIT(ull, idx);
    assertBitIsOne_ull(ull, idx);
    CLEAR_BIT(ull, idx);
    assertBitIsZero_ull(ull, idx);
  }

  for (idx = 0; idx < 64; idx += 1) {
    assertBitIsZero_sll(sll, idx);
    SET_BIT(sll, idx);
    assertBitIsOne_sll(sll, idx);
    CLEAR_BIT(sll, idx);
    assertBitIsZero_sll(sll, idx);
  }
}

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
      exit(1);
    } else {
      totalChecksPerformed += 1;
    }
  }

  for (idx = 0; idx < 32; idx += 1) {
    SET_BIT(bBoard, board120to64[squares[idx]]);
    SET_BIT(bBoard, board120to64[squares[idx]]);

    CLEAR_BIT(bBoard, board120to64[squares[idx]]);

    if (bBoard != 0ULL) {
      printf("Double SET_BIT run: set & clear %s fail!\n\n", squaresStr[idx]);
      exit(1);
    } else {
      totalChecksPerformed += 1;
    }
  }

  for (idx = 0; idx < 32; idx += 1) {
    SET_BIT(bBoard, board120to64[squares[idx]]);

    CLEAR_BIT(bBoard, board120to64[squares[idx]]);
    CLEAR_BIT(bBoard, board120to64[squares[idx]]);

    if (bBoard != 0ULL) {
      printf("Double CLEAR_BIT run: set & clear %s fail!\n\n", squaresStr[idx]);
      exit(1);
    } else {
      totalChecksPerformed += 1;
    }
  }
}

void countTests()
{
  unsigned long long bBoard = 0ULL;
  unsigned char bitCount = count_1s(bBoard);

  if (bitCount != 0) {
    printf("bitCount != 0; bitCount = %hhu\n\n", bitCount);
    exit(1);
  } else {
    totalChecksPerformed += 1;
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
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }

  bBoard = 18446744073709551615ULL; // (2^64) - 1 = 8446744073709551615
  bitCount = count_1s(bBoard);

  if (bitCount != 64) {
    printf("bitCount != 64; bitCount = %hhu\n\n", bitCount);
    exit(1);
  } else {
    totalChecksPerformed += 1;
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
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[D2]) {
    printf("poppedBit != board120to64[D2]; poppedBit = %hhu\n\n", poppedBit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[E2]) {
    printf("poppedBit != board120to64[E2]; poppedBit = %hhu\n\n", poppedBit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[H3]) {
    printf("poppedBit != board120to64[H3]; poppedBit = %hhu\n\n", poppedBit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }

  poppedBit = pop_1st_bit(&bBoard);
  if (poppedBit != board120to64[A5]) {
    printf("poppedBit != board120to64[A5]; poppedBit = %hhu\n\n", poppedBit);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void bitboard_tests()
{
  printf("Starting bitboard_tests...\n");

  macroTestsChar();
  macroTestsShort();
  macroTestsLong();
  macroTestsLongLong();

  setClrTests();
  countTests();
  popTests();

  printf("Done!\n\n");
}
