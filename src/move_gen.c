#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "move_gen_white.h"
#include "move_gen_black.h"
#include "do_move.h"
#include "bitboard.h"

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

  cBoard->legalMovesAvailable = cBoard->movesAvailable;
}

void removeIllegalMoves(BOARD *cBoard)
{
  unsigned long long movesCopy[MAX_POSSIBLE_MOVES_IN_POSITION];
  unsigned char movesAvailableCopy = 0;
  unsigned char legalMovesAvailableCopy = 0;

  unsigned char toPiece = 0;
  unsigned long long move = 0ULL;

  unsigned char idx1 = 0;
  unsigned char idx2 = 0;

  if (cBoard->movesAvailable == 0) {
    return;
  }

  for (idx1 = 0; idx1 < cBoard->movesAvailable; idx1 += 1) {
    movesCopy[idx1] = cBoard->moves[idx1];
  }
  movesAvailableCopy = cBoard->movesAvailable;
  legalMovesAvailableCopy = cBoard->legalMovesAvailable;

  for (idx1 = 0; idx1 < movesAvailableCopy; idx1 += 1) {
    doMove(cBoard, movesCopy[idx1]);
    moveGen(cBoard);

    for (idx2 = 0; idx2 < cBoard->movesAvailable; idx2 += 1) {
      move = cBoard->moves[idx2];
      toPiece = (move >> 20) & 0xFFULL;

      CLEAR_BIT(toPiece, 4);
      CLEAR_BIT(toPiece, 5);
      CLEAR_BIT(toPiece, 6);
      CLEAR_BIT(toPiece, 7);

      if ((toPiece == wK) || (toPiece == bK)) {
        SET_BIT(movesCopy[idx1], MOVE_BIT_ILLEGAL);
        legalMovesAvailableCopy -= 1;

        break;
      }
    }

    undoMove(cBoard);
  }

  for (idx2 = 0; idx2 < movesAvailableCopy; idx2 += 1) {
    cBoard->moves[idx2] = movesCopy[idx2];
  }
  cBoard->movesAvailable = movesAvailableCopy;
  cBoard->legalMovesAvailable = legalMovesAvailableCopy;
}
