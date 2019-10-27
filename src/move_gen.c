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

void moveGen_wP_normal_advance(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if (cBoard->pieces[square120 + 10] == EMPTY) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 + 10)) << 8;
    move |= (0ULL | wP) << 16;

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
}

void moveGen_wP_promote_advance(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char promotedPiece = 0;

  if (cBoard->pieces[square120 + 10] == EMPTY) {
    for (promotedPiece = wN; promotedPiece < wK; promotedPiece += 1) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | (square120 + 10)) << 8;
      move |= (0ULL | promotedPiece) << 16;

      SET_BIT(move, MOVE_BIT_PROMOTION);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
}

void moveGen_wP_double_advance(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if ((cBoard->pieces[square120 + 10] == EMPTY) && (cBoard->pieces[square120 + 20] == EMPTY)) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 + 20)) << 8;
    move |= (0ULL | wP) << 16;

    SET_BIT(move, MOVE_BIT_PWN_ADVANCE_2_SQ);

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
}

void moveGen_wP_normal_capture(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if ((cBoard->pieces[square120 + 9] > wK) && (cBoard->pieces[square120 + 9] != NO_SQ)) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 + 9)) << 8;
    move |= (0ULL | wP) << 16;
    move |= (0ULL | cBoard->pieces[square120 + 9]) << 20;

    SET_BIT(move, MOVE_BIT_CAPTURE);

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
  if ((cBoard->pieces[square120 + 11] > wK) && (cBoard->pieces[square120 + 11] != NO_SQ)) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 + 11)) << 8;
    move |= (0ULL | wP) << 16;
    move |= (0ULL | cBoard->pieces[square120 + 11]) << 20;

    SET_BIT(move, MOVE_BIT_CAPTURE);

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
}

void moveGen_wP_promote_capture(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char promotedPiece = 0;

  if ((cBoard->pieces[square120 + 9] > wK) && (cBoard->pieces[square120 + 9] != NO_SQ)) {
    for (promotedPiece = wN; promotedPiece < wK; promotedPiece += 1) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | (square120 + 9)) << 8;
      move |= (0ULL | promotedPiece) << 16;
      move |= (0ULL | cBoard->pieces[square120 + 9]) << 20;

      SET_BIT(move, MOVE_BIT_CAPTURE);
      SET_BIT(move, MOVE_BIT_PROMOTION);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
  if ((cBoard->pieces[square120 + 11] > wK) && (cBoard->pieces[square120 + 11] != NO_SQ)) {
    for (promotedPiece = wN; promotedPiece < wK; promotedPiece += 1) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | (square120 + 11)) << 8;
      move |= (0ULL | promotedPiece) << 16;
      move |= (0ULL | cBoard->pieces[square120 + 11]) << 20;

      SET_BIT(move, MOVE_BIT_CAPTURE);
      SET_BIT(move, MOVE_BIT_PROMOTION);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
}

void moveGen_wP_en_passant_capture(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char enPassantSq120 = 0;

  if (cBoard->enPassantFile == NO_EN_PASSANT) return;

  enPassantSq120 = FileRankTo120SQ(cBoard->enPassantFile, RANK_6);

  move = 0ULL;

  move |= (0ULL | square120);
  move |= (0ULL | enPassantSq120) << 8;
  move |= (0ULL | wP) << 16;

  SET_BIT(move, MOVE_BIT_CAPTURE);
  SET_BIT(move, MOVE_BIT_EN_PASSANT_CAPTURE);

  cBoard->moves[cBoard->movesAvailable] = move;
  cBoard->movesAvailable += 1;
}

void moveGen_wP(BOARD *cBoard, unsigned char square120)
{
  if (square120 < 39) {
    moveGen_wP_normal_advance(cBoard, square120);
    moveGen_wP_double_advance(cBoard, square120);
    moveGen_wP_normal_capture(cBoard, square120);
  } else if (square120 < 59) {
    moveGen_wP_normal_advance(cBoard, square120);
    moveGen_wP_normal_capture(cBoard, square120);
  } else if (square120 < 69) {
    moveGen_wP_normal_advance(cBoard, square120);
    moveGen_wP_normal_capture(cBoard, square120);
    moveGen_wP_en_passant_capture(cBoard, square120);
  } else if (square120 < 79) {
    moveGen_wP_normal_advance(cBoard, square120);
    moveGen_wP_normal_capture(cBoard, square120);
  } else {
    moveGen_wP_promote_advance(cBoard, square120);
    moveGen_wP_promote_capture(cBoard, square120);
  }
}

void moveGen_wN(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char idx = 0;

  unsigned char toSquare120[8] = {
    square120 - 12, // - (65 - 53)
    square120 - 21, // - (65 - 44)
    square120 - 19, // - (65 - 46)
    square120 - 8,  // - (65 - 57)

    square120 + 12, // - (65 - 77)
    square120 + 21, // - (65 - 86)
    square120 + 19, // - (65 - 84)
    square120 + 8   // - (65 - 73)
  };

  for (idx = 0; idx < 8; idx += 1) {
    if (cBoard->pieces[toSquare120[idx]] == EMPTY) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | toSquare120[idx]) << 8;
      move |= (0ULL | wN) << 16;

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    } else if ((cBoard->pieces[toSquare120[idx]] > wK) && (cBoard->pieces[toSquare120[idx]] != NO_SQ)) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | toSquare120[idx]) << 8;
      move |= (0ULL | wN) << 16;
      move |= (0ULL | cBoard->pieces[toSquare120[idx]]) << 20;

      SET_BIT(move, MOVE_BIT_CAPTURE);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
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
        SET_BIT(move, 29);

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

  for (piece = 1; piece < 13; piece += 1) {
    cBoard->numPieces[piece] = 0;
  }

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
