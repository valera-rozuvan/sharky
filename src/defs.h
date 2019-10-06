#ifndef __DEFS_H__
#define __DEFS_H__

typedef unsigned long long U64;
typedef unsigned char U8;

#define PROGRAM_NAME "Sharky"
#define PROGRAM_VERSION "0.0.4"

// Number of squares on our virtual board.
#define BOARD_SQ_NUM 120

// Maximum number of half moves per game.
#define MAX_GAME_MOVES_NUM 1600

// Empty square, and pieces.
enum {
  EMPTY,
  wP, wN, wB, wR, wQ, wK,
  bP, bN, bB, bR, bQ, bW
};

// Files and ranks.
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };

// Piece colors.
enum { WHITE, BLACK, BOTH };

// Board squares.
enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 31, B2, C2, D2, E2, F2, G2, H2,
  A3 = 41, B3, C3, D3, E3, F3, G3, H3,
  A4 = 51, B4, C4, D4, E4, F4, G4, H4,
  A5 = 61, B5, C5, D5, E5, F5, G5, H5,
  A6 = 71, B6, C6, D6, E6, F6, G6, H6,
  A7 = 81, B7, C7, D7, E7, F7, G7, H7,
  A8 = 91, B8, C8, D8, E8, F8, G8, H8,

  NO_SQ
};

// Booleans.
enum { FALSE, TRUE };

// Castling information. Will be used to mark bits.
enum { WKCastling = 1, WQCastling = 2, BKCastling = 4, BQCastling = 8 };

#endif

