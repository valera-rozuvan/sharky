/*
 * Define arrays to convert indexes between two virtual representations
 * of the chess board.
 *
 * Board120. Array with length of 120. It can be represented as follows.
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
 * Board64. Actual chess board has 64 squares, and will be represented as
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
 * of one array (64 size board) to the other (120 size board). For this we will have
 * precomputed arrays with indexes of one array pointing to values of indexes
 * of the other array. And vice versa.
 *
 * For example:
 *
 *   board64to120[13] = 36
 *   board120to64[42] = 17
 *
 */

#include "stdio.h"

#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "bitboard.h"
#include "zobrist_hashing.h"

unsigned char board64to120[64] = {
   21,   22,   23,   24,   25,   26,   27,   28,
   31,   32,   33,   34,   35,   36,   37,   38,
   41,   42,   43,   44,   45,   46,   47,   48,
   51,   52,   53,   54,   55,   56,   57,   58,
   61,   62,   63,   64,   65,   66,   67,   68,
   71,   72,   73,   74,   75,   76,   77,   78,
   81,   82,   83,   84,   85,   86,   87,   88,
   91,   92,   93,   94,   95,   96,   97,   98
};
unsigned char board120to64[120] = {
   99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
   99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
   99,    0,    1,    2,    3,    4,    5,    6,    7,   99,
   99,    8,    9,   10,   11,   12,   13,   14,   15,   99,
   99,   16,   17,   18,   19,   20,   21,   22,   23,   99,
   99,   24,   25,   26,   27,   28,   29,   30,   31,   99,
   99,   32,   33,   34,   35,   36,   37,   38,   39,   99,
   99,   40,   41,   42,   43,   44,   45,   46,   47,   99,
   99,   48,   49,   50,   51,   52,   53,   54,   55,   99,
   99,   56,   57,   58,   59,   60,   61,   62,   63,   99,
   99,   99,   99,   99,   99,   99,   99,   99,   99,   99,
   99,   99,   99,   99,   99,   99,   99,   99,   99,   99
};

void printBoard64(unsigned long long bBoard) {
  char rankIter = 0;
  char fileIter = 0;
  unsigned char sq120 = 0;
  unsigned char sq64 = 0;

  rankIter = RANK_8;
  do {
    fileIter = FILE_A;

    do {
      sq120 = FileRankTo120SQ(fileIter, rankIter);
      sq64 = board120to64[sq120];

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

const char *boardPieceStr[13] = {
  ".",
  "P", "N", "B", "R", "Q", "K",
  "p", "n", "b", "r", "q", "k"
};

const char* sideToMoveStr(BOARD *cBoard)
{
  if (cBoard->side == WHITE) return "white";
  if (cBoard->side == BLACK) return "black";

  return "?";
}

const char *BIT_CASTLING_CHAR[4] = {
  "K", "Q", "k", "q"
};

const char* castlingPermStr(BOARD *cBoard, unsigned char bitToTest)
{
  if (CHECK_BIT(cBoard->castlingPerm, bitToTest)) return BIT_CASTLING_CHAR[bitToTest];

  return "-";
}

void printBoard(BOARD *cBoard) {
  char rankIter = 0;
  char fileIter = 0;
  unsigned char sq120 = 0;

  rankIter = RANK_8;
  do {
    fileIter = FILE_A;

    printf("%hhi ", rankIter + 1);

    do {
      sq120 = FileRankTo120SQ(fileIter, rankIter);

      if (cBoard->pieces[sq120] >= 13) {
        printf("?");
      } else {
        printf("%3s", boardPieceStr[cBoard->pieces[sq120]]);
      }

      fileIter += 1;
    } while (fileIter <= FILE_H);

    printf("\n");
    rankIter -= 1;
  } while (rankIter >= RANK_1);

  printf("\n  ");
  fileIter = FILE_A;
  do {
    printf("%3c", 'a' + fileIter);

    fileIter += 1;
  } while (fileIter <= FILE_H);
  printf("\n\n");

  printf("Position hash: %llx\n", cBoard->positionKey);
  printf("Side to move: %s\n", sideToMoveStr(cBoard));
  if (cBoard->castlingPerm != 0) {
    printf(
      "Castling rights: %s%s%s%s\n",
      castlingPermStr(cBoard, WKCastling),
      castlingPermStr(cBoard, WQCastling),
      castlingPermStr(cBoard, BKCastling),
      castlingPermStr(cBoard, BQCastling)
    );
  }

  // TODO: Print en passant file, if en passant capture is available.
}

const char *SQUARE_NAMES[64] = {
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
};

unsigned char chessMoveToStr(unsigned long long move, char fmtdMove[MAX_MOVE_STR_LENGTH])
{
  if (CHECK_BIT(move, MOVE_BIT_ILLEGAL)) {
    return 0;
  }

  unsigned char fromSq64 = board120to64[move & 0xFFULL];
  unsigned char toSq64 = board120to64[(move >> 8) & 0xFFULL];

  // Only used for showing promoted piece, if applicable.
  unsigned char promotedPiece = (move >> 16) & 0xFFULL;
  CLEAR_BIT(promotedPiece, 4);
  CLEAR_BIT(promotedPiece, 5);
  CLEAR_BIT(promotedPiece, 6);
  CLEAR_BIT(promotedPiece, 7);

  if (CHECK_BIT(move, MOVE_BIT_K_CASTLE)) {
    snprintf(fmtdMove, 4, "%s", "0-0");
  } else if (CHECK_BIT(move, MOVE_BIT_Q_CASTLE)) {
    snprintf(fmtdMove, 6, "%s", "0-0-0");
  } else if ((CHECK_BIT(move, MOVE_BIT_CAPTURE)) && (!CHECK_BIT(move, MOVE_BIT_EN_PASSANT_CAPTURE))) {
    snprintf(fmtdMove, 6, "%s%s%s", SQUARE_NAMES[fromSq64], "x", SQUARE_NAMES[toSq64]);
  } else if ((CHECK_BIT(move, MOVE_BIT_CAPTURE)) && (CHECK_BIT(move, MOVE_BIT_EN_PASSANT_CAPTURE))) {
    snprintf(fmtdMove, 10, "%s%s%s%s", SQUARE_NAMES[fromSq64], "x", SQUARE_NAMES[toSq64], "e.p.");
  } else if ((!CHECK_BIT(move, MOVE_BIT_CAPTURE)) && (CHECK_BIT(move, MOVE_BIT_PROMOTION))) {
    snprintf(fmtdMove, 7, "%s%s%s%s", SQUARE_NAMES[fromSq64], SQUARE_NAMES[toSq64], "=", boardPieceStr[promotedPiece]);
  } else if ((CHECK_BIT(move, MOVE_BIT_CAPTURE)) && (CHECK_BIT(move, MOVE_BIT_PROMOTION))) {
    snprintf(fmtdMove, 8, "%s%s%s%s%s", SQUARE_NAMES[fromSq64], "x", SQUARE_NAMES[toSq64], "=", boardPieceStr[promotedPiece]);
  } else {
    snprintf(fmtdMove, 5, "%s%s", SQUARE_NAMES[fromSq64], SQUARE_NAMES[toSq64]);
  }

  return 1;
}

void printMoves(BOARD *cBoard)
{
  unsigned char idx = 0;
  char fmtdMove[MAX_MOVE_STR_LENGTH] = "";

  if (cBoard->movesAvailable == 0) {
    printf("Moves available: none\n");

    return;
  }

  printf("Moves available: ");

  idx = 0;
  do {
    if (chessMoveToStr(cBoard->moves[idx], fmtdMove) == 1) {
      printf("%s; ", fmtdMove);
    }

    idx += 1;
  } while (idx < cBoard->movesAvailable);

  printf("\n\n");
}

void setupEmptyPosition(BOARD *cBoard)
{
  unsigned char idx = 0;

  for (idx = 0; idx < 120; idx += 1) {
    cBoard->pieces[idx] = NO_SQ;
  }

  for (idx = 0; idx < 64; idx += 1) {
    cBoard->pieces[board64to120[idx]] = EMPTY;
  }

  cBoard->castlingPerm = 0ULL;
  cBoard->side = WHITE;
  cBoard->enPassantFile = NO_EN_PASSANT;
  cBoard->fiftyMove = 0;
  cBoard->historyPly = 0;

  for (idx = 0; idx < MAX_POSSIBLE_MOVES_IN_POSITION; idx += 1) {
    cBoard->moves[idx] = 0ULL;
  }
  cBoard->movesAvailable = 0;

  for (idx = 1; idx < 13; idx += 1) {
    cBoard->numPieces[idx] = 0;
  }

  cBoard->positionKey = generateFullHash(cBoard);
}

void setupInitialPosition(BOARD *cBoard)
{
  unsigned char idx = 0;

  for (idx = 0; idx < 120; idx += 1) {
    cBoard->pieces[idx] = NO_SQ;
  }

  for (idx = 0; idx < 64; idx += 1) {
    cBoard->pieces[board64to120[idx]] = EMPTY;
  }

  cBoard->pieces[A1] = wR;
  cBoard->pieces[B1] = wN;
  cBoard->pieces[C1] = wB;
  cBoard->pieces[D1] = wQ;
  cBoard->pieces[E1] = wK;
  cBoard->pieces[F1] = wB;
  cBoard->pieces[G1] = wN;
  cBoard->pieces[H1] = wR;

  for (idx = A2; idx <= H2; idx += 1) {
    cBoard->pieces[idx] = wP;
  }

  for (idx = A7; idx <= H7; idx += 1) {
    cBoard->pieces[idx] = bP;
  }

  cBoard->pieces[A8] = bR;
  cBoard->pieces[B8] = bN;
  cBoard->pieces[C8] = bB;
  cBoard->pieces[D8] = bQ;
  cBoard->pieces[E8] = bK;
  cBoard->pieces[F8] = bB;
  cBoard->pieces[G8] = bN;
  cBoard->pieces[H8] = bR;

  cBoard->castlingPerm = 0ULL;

  SET_BIT(cBoard->castlingPerm, WKCastling);
  SET_BIT(cBoard->castlingPerm, WQCastling);
  SET_BIT(cBoard->castlingPerm, BKCastling);
  SET_BIT(cBoard->castlingPerm, BQCastling);

  cBoard->side = WHITE;

  cBoard->enPassantFile = NO_EN_PASSANT;

  cBoard->fiftyMove = 0;
  cBoard->historyPly = 0;

  for (idx = 0; idx < MAX_POSSIBLE_MOVES_IN_POSITION; idx += 1) {
    cBoard->moves[idx] = 0ULL;
  }
  cBoard->movesAvailable = 0;

  for (idx = 1; idx < 13; idx += 1) {
    cBoard->numPieces[idx] = 0;
  }

  cBoard->positionKey = generateFullHash(cBoard);
}
