#include <stdio.h>

#include "board.h"
#include "defs.h"
#include "bitboard.h"
#include "board_routines.h"

void doMove(BOARD *cBoard, unsigned long long move)
{
  unsigned char fromSq120 = move & 0xFFULL;
  unsigned char toSq120 = (move >> 8) & 0xFFULL;

  unsigned char fromPiece = (move >> 16) & 0xFFULL;
  // unsigned char toPiece = (move >> 20) & 0xFFULL;

  CLEAR_BIT(fromPiece, 4);
  CLEAR_BIT(fromPiece, 5);
  CLEAR_BIT(fromPiece, 6);
  CLEAR_BIT(fromPiece, 7);

  // CLEAR_BIT(toPiece, 4);
  // CLEAR_BIT(toPiece, 5);
  // CLEAR_BIT(toPiece, 6);
  // CLEAR_BIT(toPiece, 7);

  // printf("fromSq120 = %hhu, toSq120 = %hhu, fromPiece = %hhu, toPiece = %hhu\n", fromSq120, toSq120, fromPiece, toPiece);

  cBoard->pieces[fromSq120] = EMPTY;
  cBoard->pieces[toSq120] = fromPiece;

  if ((fromPiece == wP) || (fromPiece == bP) || (CHECK_BIT(move, MOVE_BIT_CAPTURE))) {
    cBoard->fiftyMove = 0;
  } else {
    cBoard->fiftyMove += 1;
  }

  if (CHECK_BIT(move, MOVE_BIT_EN_PASSANT_CAPTURE)) {
    if (cBoard->side == WHITE) {
      cBoard->pieces[toSq120 - 10] = EMPTY;
    } else {
      cBoard->pieces[toSq120 + 10] = EMPTY;
    }
  } else if (CHECK_BIT(move, MOVE_BIT_PROMOTION)) {
    // Do nothing. This flag is only useful for undoing moves.
  } else if (CHECK_BIT(move, MOVE_BIT_PWN_ADVANCE_2_SQ)) {
    cBoard->enPassantFile = board120toFile[fromSq120];
  } else if (CHECK_BIT(move, MOVE_BIT_K_CASTLE)) {
    if (cBoard->side == WHITE) {
      cBoard->pieces[H1] = EMPTY;
      cBoard->pieces[F1] = wR;
    } else {
      cBoard->pieces[H8] = EMPTY;
      cBoard->pieces[F8] = bR;
    }
  } else if (CHECK_BIT(move, MOVE_BIT_Q_CASTLE)) {
    if (cBoard->side == WHITE) {
      cBoard->pieces[A1] = EMPTY;
      cBoard->pieces[D1] = wR;
    } else {
      cBoard->pieces[A8] = EMPTY;
      cBoard->pieces[D8] = bR;
    }
  }

  if (cBoard->side == WHITE) {
    cBoard->side = BLACK;
  } else {
    cBoard->side = WHITE;
  }

  cBoard->historyPly += 1;
}
