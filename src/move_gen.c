#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "bitboard.h"

/* ----------------- */

void moveGen_EMPTY(BOARD *cBoard, unsigned char square120)
{
  // We never call this function, so just have dummy code here.
  cBoard->pieces[square120] = EMPTY;
}

/* ----------------- */

void moveGen_wP(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wP;
}

void moveGen_wN(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wN;
}

void moveGen_wB(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wB;
}

void moveGen_wR(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wR;
}

void moveGen_wQ(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wQ;
}

void moveGen_wK(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wK;
}

/* ----------------- */

void moveGen_bP(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  cBoard->pieces[square120] = bP;

  if (square120 > 80) {
    // The black pawn is on rank 7. We can do normal move and 2 square advance.

    if (cBoard->pieces[square120 - 10] == EMPTY) {
      move |= (0ULL | square120);
      move |= (0ULL | (square120 - 10)) << 8;
      move |= (0ULL | bP) << 16;

      SET_BIT(move, 28);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;

      // Can we advance 2 squares?
      if (cBoard->pieces[square120 - 20] == EMPTY) {
        move = 0ULL;

        move |= (0ULL | square120);
        move |= (0ULL | (square120 - 20)) << 8;
        move |= (0ULL | bP) << 16;

        SET_BIT(move, 28);

        cBoard->moves[cBoard->movesAvailable] = move;
        cBoard->movesAvailable += 1;
      }
    }
  }
}

void moveGen_bN(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bN;
}

void moveGen_bB(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bB;
}

void moveGen_bR(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bR;
}

void moveGen_bQ(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bQ;
}

void moveGen_bK(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bK;
}

/* ----------------- */

void (*MOVE_GEN[13])(BOARD *cBoard, unsigned char square120) = {
  moveGen_EMPTY,

  moveGen_wP,
  moveGen_wN,
  moveGen_wB,
  moveGen_wR,
  moveGen_wQ,
  moveGen_wK,

  moveGen_bP,
  moveGen_bN,
  moveGen_bB,
  moveGen_bR,
  moveGen_bQ,
  moveGen_bK
};

void moveGen(BOARD *cBoard)
{
  unsigned char piece;
  unsigned char square120;
  unsigned char square64;

  for (square64 = 0; square64 < 64; square64 += 1) {
    square120 = board64to120[square64];
    piece = cBoard->pieces[square120];

    if (piece == EMPTY) continue;

    (*MOVE_GEN[piece])(cBoard, square120);
  }
}
