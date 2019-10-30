#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "move_gen_white.h"
#include "move_gen_black.h"

/* ----------------- */

void moveGen_EMPTY(BOARD *cBoard, unsigned char square120)
{
  // We never call this function, so just have dummy code here.
  cBoard->pieces[square120] = EMPTY;
}

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

/*
 * Generates pseudo-legal moves for a given chess position.
 */
void moveGen(BOARD *cBoard)
{
  unsigned char piece;
  unsigned char square120;
  unsigned char square64;

  for (piece = 1; piece < 13; piece += 1) {
    cBoard->numPieces[piece] = 0;
  }

  // Set move count to zero. We don't initialize cBoard->moves array because
  // newly generated moves will overwrite the old ones (if any).
  cBoard->movesAvailable = 0;

  if (cBoard->side == WHITE) {
    for (square64 = 0; square64 < 64; square64 += 1) {
      square120 = board64to120[square64];
      piece = cBoard->pieces[square120];

      if (piece == EMPTY) continue;
      cBoard->numPieces[piece] += 1;
      if (piece > wK) continue;

      (*MOVE_GEN[piece])(cBoard, square120);
    }
  } else {
    for (square64 = 0; square64 < 64; square64 += 1) {
      square120 = board64to120[square64];
      piece = cBoard->pieces[square120];

      if (piece == EMPTY) continue;
      cBoard->numPieces[piece] += 1;
      if (piece < bP) continue;

      (*MOVE_GEN[piece])(cBoard, square120);
    }
  }
}
