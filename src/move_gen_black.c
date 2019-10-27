#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "bitboard.h"

void moveGen_bP_normal_advance(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if (cBoard->pieces[square120 - 10] == EMPTY) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 - 10)) << 8;
    move |= (0ULL | bP) << 16;

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
}

void moveGen_bP_promote_advance(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char promotedPiece = 0;

  if (cBoard->pieces[square120 - 10] == EMPTY) {
    for (promotedPiece = bN; promotedPiece < bK; promotedPiece += 1) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | (square120 - 10)) << 8;
      move |= (0ULL | promotedPiece) << 16;

      SET_BIT(move, MOVE_BIT_PROMOTION);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
}

void moveGen_bP_double_advance(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if ((cBoard->pieces[square120 - 10] == EMPTY) && (cBoard->pieces[square120 - 20] == EMPTY)) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 - 20)) << 8;
    move |= (0ULL | bP) << 16;

    SET_BIT(move, MOVE_BIT_PWN_ADVANCE_2_SQ);

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
}

void moveGen_bP_normal_capture(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if ((cBoard->pieces[square120 - 9] >= wP) && (cBoard->pieces[square120 - 9] <= wK)) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 - 9)) << 8;
    move |= (0ULL | bP) << 16;
    move |= (0ULL | cBoard->pieces[square120 - 9]) << 20;

    SET_BIT(move, MOVE_BIT_CAPTURE);

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
  if ((cBoard->pieces[square120 - 11] >= wP) && (cBoard->pieces[square120 - 11] <= wK)) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 - 11)) << 8;
    move |= (0ULL | bP) << 16;
    move |= (0ULL | cBoard->pieces[square120 - 11]) << 20;

    SET_BIT(move, MOVE_BIT_CAPTURE);

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
}

void moveGen_bP_promote_capture(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char promotedPiece = 0;

  if ((cBoard->pieces[square120 - 9] >= wP) && (cBoard->pieces[square120 - 9] <= wK)) {
    for (promotedPiece = bN; promotedPiece < bK; promotedPiece += 1) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | (square120 - 9)) << 8;
      move |= (0ULL | promotedPiece) << 16;
      move |= (0ULL | cBoard->pieces[square120 - 9]) << 20;

      SET_BIT(move, MOVE_BIT_CAPTURE);
      SET_BIT(move, MOVE_BIT_PROMOTION);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
  if ((cBoard->pieces[square120 - 11] >= wP) && (cBoard->pieces[square120 - 11] <= wK)) {
    for (promotedPiece = bN; promotedPiece < bK; promotedPiece += 1) {
      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | (square120 - 11)) << 8;
      move |= (0ULL | promotedPiece) << 16;
      move |= (0ULL | cBoard->pieces[square120 - 11]) << 20;

      SET_BIT(move, MOVE_BIT_CAPTURE);
      SET_BIT(move, MOVE_BIT_PROMOTION);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
}

void moveGen_bP_en_passant_capture(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char enPassantSq120 = 0;

  if (cBoard->enPassantFile == NO_EN_PASSANT) return;

  enPassantSq120 = FileRankTo120SQ(cBoard->enPassantFile, RANK_3);

  move = 0ULL;

  move |= (0ULL | square120);
  move |= (0ULL | enPassantSq120) << 8;
  move |= (0ULL | bP) << 16;

  SET_BIT(move, MOVE_BIT_CAPTURE);
  SET_BIT(move, MOVE_BIT_EN_PASSANT_CAPTURE);

  cBoard->moves[cBoard->movesAvailable] = move;
  cBoard->movesAvailable += 1;
}

void moveGen_bP(BOARD *cBoard, unsigned char square120)
{
  if (square120 < 39) {
    moveGen_bP_promote_advance(cBoard, square120);
    moveGen_bP_promote_capture(cBoard, square120);
  } else if (square120 < 49) {
    moveGen_bP_normal_advance(cBoard, square120);
    moveGen_bP_normal_capture(cBoard, square120);
  } else if (square120 < 59) {
    moveGen_bP_normal_advance(cBoard, square120);
    moveGen_bP_normal_capture(cBoard, square120);
    moveGen_bP_en_passant_capture(cBoard, square120);
  } else if (square120 < 79) {
    moveGen_bP_normal_advance(cBoard, square120);
    moveGen_bP_normal_capture(cBoard, square120);
  } else {
    moveGen_bP_normal_advance(cBoard, square120);
    moveGen_bP_double_advance(cBoard, square120);
    moveGen_bP_normal_capture(cBoard, square120);
  }
}

void moveGen_bN(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;
  unsigned char idx = 0;
  unsigned char toSquare120 = 0;

  unsigned char toSquares120[8] = {
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
    toSquare120 = toSquares120[idx];

    if (cBoard->pieces[toSquare120] == EMPTY) {
      // Normal move.

      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | toSquare120) << 8;
      move |= (0ULL | bN) << 16;

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    } else if ((cBoard->pieces[toSquare120] >= wP) && (cBoard->pieces[toSquare120] <= wK)) {
      // Normal capture.

      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | toSquare120) << 8;
      move |= (0ULL | bN) << 16;
      move |= (0ULL | cBoard->pieces[toSquare120]) << 20;

      SET_BIT(move, MOVE_BIT_CAPTURE);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
}

void moveGen_black_sliding_piece(
  BOARD *cBoard, unsigned char square120,
  unsigned char piece, unsigned char (*moveDisplacements)[], unsigned char moveDisplacementsCount
)
{
  unsigned long long move = 0ULL;
  unsigned char toSquare120 = 0;
  unsigned char idx1 = 0;
  unsigned char idx2 = 0;
  unsigned char maxMovesInDirection = 10;

  if (piece == bK) maxMovesInDirection = 1;

  for (idx1 = 0; idx1 < moveDisplacementsCount; idx1 += 1) {
    toSquare120 = square120 + (*moveDisplacements)[idx1];

    for (idx2 = 0; idx2 < maxMovesInDirection; idx2 += 1) {
      if (cBoard->pieces[toSquare120] == EMPTY) {
        move = 0ULL;

        move |= (0ULL | square120);
        move |= (0ULL | toSquare120) << 8;
        move |= (0ULL | piece) << 16;

        cBoard->moves[cBoard->movesAvailable] = move;
        cBoard->movesAvailable += 1;
      } else if (cBoard->pieces[toSquare120] == NO_SQ) {
        break;
      } else if (cBoard->pieces[toSquare120] < bP) {
        move = 0ULL;

        move |= (0ULL | square120);
        move |= (0ULL | toSquare120) << 8;
        move |= (0ULL | piece) << 16;
        move |= (0ULL | cBoard->pieces[toSquare120]) << 20;

        SET_BIT(move, MOVE_BIT_CAPTURE);

        cBoard->moves[cBoard->movesAvailable] = move;
        cBoard->movesAvailable += 1;

        break;
      } else {
        break;
      }

      toSquare120 += (*moveDisplacements)[idx1];
    }
  }
}

void moveGen_bB(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[4] = { -11, -9, 11, 9 };
  moveGen_black_sliding_piece(cBoard, square120, bB, &moveDisplacements, 4);
}

void moveGen_bR(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[4] = { -10, -1, 10, 1 };
  moveGen_black_sliding_piece(cBoard, square120, bR, &moveDisplacements, 4);
}

void moveGen_bQ(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[8] = { -11, -9, 11, 9, -10, -1, 10, 1 };
  moveGen_black_sliding_piece(cBoard, square120, bQ, &moveDisplacements, 8);
}

void moveGen_bK(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[8] = { -11, -9, 11, 9, -10, -1, 10, 1 };
  moveGen_black_sliding_piece(cBoard, square120, bK, &moveDisplacements, 8);
}
