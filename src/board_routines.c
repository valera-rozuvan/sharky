/*
 * Routines to convert indexes between our two virtual representations
 * of the chess board.
 *
 * Array with length of 120. It can be represented as follows.
 * 10 by 12 items. In the center is the chess board. We have buffer
 * zones at the top, left, right, and bottom. Top and bottom
 * buffer zones have 2 rows to accommodate for generating knight
 * moves. Left and right buffer zones don't have 2 columns because
 * they extend (overlap) to each other.
 *
 * .-----------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |
 * | 000 | 001 | 002 | 003 | 004 | 005 | 006 | 007 | 008 | 009 |
 * |-----------------------------------------------------------|
 * |     |     |     |     |     |     |     |     |     |     |
 * | 010 | 011 | 012 | 013 | 014 | 015 | 016 | 017 | 018 | 019 |
 * |-----.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.-----|
 * |     I*****|     |*****|     |*****|     |*****|     I     |
 * | 020 I*021*| 022 |*023*| 024 |*025*| 026 |*027*| 028 I 029 |
 * |-----I-----------------------------------------------I-----|
 * |     I     |*****|     |*****|     |*****|     |*****I     |
 * | 030 I 031 |*032*| 033 |*034*| 035 |*036*| 037 |*038*I 039 |
 * |-----I-----------------------------------------------I-----|
 * |     I*****|     |*****|     |*****|     |*****|     I     |
 * | 040 I*041*| 042 |*043*| 044 |*045*| 046 |*047*| 048 I 049 |
 * |-----I-----------------------------------------------I-----|
 * |     I     |*****|     |*****|     |*****|     |*****I     |
 * | 050 I 051 |*052*| 053 |*054*| 055 |*056*| 057 |*058*I 059 |
 * |-----I-----------------------------------------------I-----|
 * |     I*****|     |*****|     |*****|     |*****|     I     |
 * | 060 I*061*| 062 |*063*| 064 |*065*| 066 |*067*| 068 I 069 |
 * |-----I-----------------------------------------------I-----|
 * |     I     |*****|     |*****|     |*****|     |*****I     |
 * | 070 I 071 |*072*| 073 |*074*| 075 |*076*| 077 |*078*I 079 |
 * |-----I-----------------------------------------------I-----|
 * |     I*****|     |*****|     |*****|     |*****|     I     |
 * | 080 I*081*| 082 |*083*| 084 |*085*| 086 |*087*| 088 I 089 |
 * |-----I-----------------------------------------------I-----|
 * |     I     |*****|     |*****|     |*****|     |*****I     |
 * | 090 I 091 |*092*| 093 |*094*| 095 |*096*| 097 |*098*I 099 |
 * |-----^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^-----|
 * |     |     |     |     |     |     |     |     |     |     |
 * | 100 | 101 | 102 | 103 | 104 | 105 | 106 | 107 | 108 | 109 |
 * |-----------------------------------------------------------|
 * |     |     |     |     |     |     |     |     |     |     |
 * | 110 | 111 | 112 | 113 | 114 | 115 | 116 | 117 | 118 | 119 |
 * ^-----------------------------------------------------------^
 *
 * Actual chess board has 64 squares, and will be represented as
 * rotated. Below you can see the visualization of the array length 64.
 * 8 by 8 items.
 *
 *         FILE_A  FILE_B  FILE_C  FILE_D  FILE_E  FILE_F  FILE_G  FILE_H
 *        .---------------------------------------------------------------.
 *        |       |       |       |       |       |       |       |       |
 * RANK_1 |00 [A1]|01 [B1]|02 [C1]|03 [D1]|04 [E1]|05 [F1]|06 [G1]|07 [H1]|
 *        |       |       |       |       |       |       |       |       |
 *        |---------------------------------------------------------------|
 *        |       |       |       |       |       |       |       |       |
 * RANK_2 |08 [A2]|09 [B2]|10 [C2]|11 [D2]|12 [E2]|13 [F2]|14 [G2]|15 [H2]|
 *        |       |       |       |       |       |       |       |       |
 *        |---------------------------------------------------------------|
 *        |       |       |       |       |       |       |       |       |
 * RANK_3 |16 [A3]|17 [B3]|18 [C3]|19 [D3]|20 [E3]|21 [F3]|22 [G3]|23 [H3]|
 *        |       |       |       |       |       |       |       |       |
 *        |---------------------------------------------------------------|
 *        |       |       |       |       |       |       |       |       |
 * RANK_4 |24 [A4]|25 [B4]|26 [C4]|27 [D4]|28 [E4]|29 [F4]|30 [G4]|31 [H4]|
 *        |       |       |       |       |       |       |       |       |
 *        |---------------------------------------------------------------|
 *        |       |       |       |       |       |       |       |       |
 * RANK_5 |32 [A5]|33 [B5]|34 [C5]|35 [D5]|36 [E5]|37 [F5]|38 [G5]|39 [H5]|
 *        |       |       |       |       |       |       |       |       |
 *        |---------------------------------------------------------------|
 *        |       |       |       |       |       |       |       |       |
 * RANK_6 |40 [A6]|41 [B6]|42 [C6]|43 [D6]|44 [E6]|45 [F6]|46 [G6]|47 [H6]|
 *        |       |       |       |       |       |       |       |       |
 *        |---------------------------------------------------------------|
 *        |       |       |       |       |       |       |       |       |
 * RANK_7 |48 [A7]|49 [B7]|50 [C7]|51 [D7]|52 [E7]|53 [F7]|54 [G7]|55 [H7]|
 *        |       |       |       |       |       |       |       |       |
 *        |---------------------------------------------------------------|
 *        |       |       |       |       |       |       |       |       |
 * RANK_8 |56 [A8]|57 [B8]|58 [C8]|59 [D8]|60 [E8]|61 [F8]|62 [G8]|63 [H8]|
 *        |       |       |       |       |       |       |       |       |
 *        ^---------------------------------------------------------------^
 *
 * So, we need two routines to be able to quickly convert between coordinates
 * of one array (64 size) to the other (120 size). For this we will have
 * precomputed arrays with indexes of one array pointing to values of indexes
 * of the other array. And vice versa.
 *
 * For example:
 *
 *   arr64to120[13] = 36
 *   arr120to64[42] = 17
 *
 * The values of these two conversion arrays will be initialized by method
 * initBoardCoordConv(), which should be called at the start of the program.
 *
 */

#include "stdio.h"

#include "defs.h"
#include "board.h"
#include "board_routines.h"

U8 arr64to120[64];
U8 arr120to64[BOARD_SQ_NUM];

void initBoardCoordConvArrays() {
  U8 idx = 0;
  U8 fileIter = FILE_A;
  U8 rankIter = RANK_1;
  U8 suqareIter = A1;

  // Counter for the 64 length array.
  U8 square64 = 0;

  // Initialize the bigger array to out of bounds values. The buffer squares should
  // not lead to a square on the 64 bit board.
  for (idx = 0; idx < BOARD_SQ_NUM; ++idx) {
    arr120to64[idx] = 64;
  }

  // Now we setup actual useful values.
  for (rankIter = RANK_1; rankIter <= RANK_8; ++rankIter) {
    for (fileIter = FILE_A; fileIter <= FILE_H; ++fileIter) {
      suqareIter = FileRank2SQ(fileIter, rankIter);

      arr64to120[square64] = suqareIter;
      arr120to64[suqareIter] = square64;

      square64 += 1;
    }
  }
}

void printBoardCoordConvArrays() {
  printf("arr120to64 =>\n");

  U8 idx = 0;

  for (idx = 0; idx < BOARD_SQ_NUM; ++idx) {
    if (idx % 10 == 0) {
      printf("\n");
    }

    printf("%5d", arr120to64[idx]);
  }

  printf("\n\n");
  printf("arr64to120 =>\n");

  for (idx = 0; idx < 64; ++idx) {
    if (idx % 8 == 0) {
      printf("\n");
    }

    printf("%5d", arr64to120[idx]);
  }

  printf("\n\n");
}

