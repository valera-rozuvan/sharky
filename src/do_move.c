#include <stdio.h>

#include "board.h"
#include "defs.h"
#include "bitboard.h"
#include "board_routines.h"
#include "zobrist_hashing.h"

void doMove(BOARD *cBoard, unsigned long long move)
{
  UNDO_MOVE undoMove = {
    .move = move, .castlingPerm = 0, .enPassantFile = 0, .fiftyMove = 0, .positionKey = 0
  };

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

  if (CHECK_BIT(move, MOVE_BIT_PWN_ADVANCE_2_SQ)) {
    cBoard->enPassantFile = board120toFile[fromSq120];
  }

  if (cBoard->side == WHITE) {
    if (CHECK_BIT(move, MOVE_BIT_EN_PASSANT_CAPTURE)) {
      cBoard->pieces[toSq120 - 10] = EMPTY;
    } else if (CHECK_BIT(move, MOVE_BIT_K_CASTLE)) {
      cBoard->pieces[H1] = EMPTY;
      cBoard->pieces[F1] = wR;
    } else if (CHECK_BIT(move, MOVE_BIT_Q_CASTLE)) {
      cBoard->pieces[A1] = EMPTY;
      cBoard->pieces[D1] = wR;
    }

    if ((fromPiece == wP) || (CHECK_BIT(move, MOVE_BIT_CAPTURE))) {
      cBoard->fiftyMove = 0;
    } else {
      cBoard->fiftyMove += 1;
    }

    if (fromPiece == wK) {
      CLEAR_BIT(cBoard->castlingPerm, WKCastling);
      CLEAR_BIT(cBoard->castlingPerm, WQCastling);
    } else if (fromPiece == wR) {
      if (fromSq120 == H1) {
        CLEAR_BIT(cBoard->castlingPerm, WKCastling);
      } else if (fromSq120 == A1) {
        CLEAR_BIT(cBoard->castlingPerm, WQCastling);
      }
    }

    cBoard->side = BLACK;
  } else {
    if (CHECK_BIT(move, MOVE_BIT_EN_PASSANT_CAPTURE)) {
      cBoard->pieces[toSq120 + 10] = EMPTY;
    } else if (CHECK_BIT(move, MOVE_BIT_K_CASTLE)) {
      cBoard->pieces[H8] = EMPTY;
      cBoard->pieces[F8] = bR;
    } else if (CHECK_BIT(move, MOVE_BIT_Q_CASTLE)) {
      cBoard->pieces[A8] = EMPTY;
      cBoard->pieces[D8] = bR;
    }

    if ((fromPiece == bP) || (CHECK_BIT(move, MOVE_BIT_CAPTURE))) {
      cBoard->fiftyMove = 0;
    } else {
      cBoard->fiftyMove += 1;
    }

    if (fromPiece == bK) {
      CLEAR_BIT(cBoard->castlingPerm, BKCastling);
      CLEAR_BIT(cBoard->castlingPerm, BQCastling);
    } else if (fromPiece == bR) {
      if (fromSq120 == H8) {
        CLEAR_BIT(cBoard->castlingPerm, BKCastling);
      } else if (fromSq120 == A8) {
        CLEAR_BIT(cBoard->castlingPerm, BQCastling);
      }
    }

    cBoard->side = WHITE;
  }

  cBoard->positionKey = generateFullHash(cBoard);

  undoMove.castlingPerm = cBoard->castlingPerm;
  undoMove.enPassantFile = cBoard->enPassantFile;
  undoMove.fiftyMove = cBoard->fiftyMove;
  undoMove.positionKey = cBoard->positionKey;

  cBoard->history[cBoard->historyPly] = undoMove;

  cBoard->historyPly += 1;
}
