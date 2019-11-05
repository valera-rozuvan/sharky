#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "bitboard.h"

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

  if ((cBoard->pieces[square120 + 9] >= bP) && (cBoard->pieces[square120 + 9] <= bK)) {
    move = 0ULL;

    move |= (0ULL | square120);
    move |= (0ULL | (square120 + 9)) << 8;
    move |= (0ULL | wP) << 16;
    move |= (0ULL | cBoard->pieces[square120 + 9]) << 20;

    SET_BIT(move, MOVE_BIT_CAPTURE);

    cBoard->moves[cBoard->movesAvailable] = move;
    cBoard->movesAvailable += 1;
  }
  if ((cBoard->pieces[square120 + 11] >= bP) && (cBoard->pieces[square120 + 11] <= bK)) {
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

  if ((cBoard->pieces[square120 + 9] >= bP) && (cBoard->pieces[square120 + 9] <= bK)) {
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
  if ((cBoard->pieces[square120 + 11] >= bP) && (cBoard->pieces[square120 + 11] <= bK)) {
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

  if ((board120toFile[square120] - cBoard->enPassantFile != 1) && (cBoard->enPassantFile - board120toFile[square120] != 1)) return;

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
      move |= (0ULL | wN) << 16;

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    } else if ((cBoard->pieces[toSquare120] >= bP) && (cBoard->pieces[toSquare120] <= bK)) {
      // Normal capture.

      move = 0ULL;

      move |= (0ULL | square120);
      move |= (0ULL | toSquare120) << 8;
      move |= (0ULL | wN) << 16;
      move |= (0ULL | cBoard->pieces[toSquare120]) << 20;

      SET_BIT(move, MOVE_BIT_CAPTURE);

      cBoard->moves[cBoard->movesAvailable] = move;
      cBoard->movesAvailable += 1;
    }
  }
}

void moveGen_white_sliding_piece(
  BOARD *cBoard, unsigned char square120,
  unsigned char piece, unsigned char (*moveDisplacements)[], unsigned char moveDisplacementsCount
)
{
  unsigned long long move = 0ULL;
  unsigned char toSquare120 = 0;
  unsigned char idx1 = 0;
  unsigned char idx2 = 0;
  unsigned char maxMovesInDirection = 10;

  if (piece == wK) maxMovesInDirection = 1;

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
      } else if (cBoard->pieces[toSquare120] > wK) {
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

unsigned char check_white_castling_path_for_attacked_squares(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[3] = { 0, 0, 0 };
  unsigned char idx1 = 0;
  unsigned char idx2 = 0;
  unsigned char checkSquare120 = 0;

  // 1. Are black pawns attacking?
  if (cBoard->pieces[square120 + 9] == bP) return 1;
  if (cBoard->pieces[square120 + 11] == bP) return 1;

  // 2. Are black knights attacking?
  if (cBoard->pieces[square120 + 12] == bN) return 1;
  if (cBoard->pieces[square120 + 21] == bN) return 1;
  if (cBoard->pieces[square120 + 19] == bN) return 1;
  if (cBoard->pieces[square120 + 8] == bN) return 1;

  // 3. Are horizontal or vertical sliding black pieces attacking?
  moveDisplacements[0] = 1;
  moveDisplacements[1] = -1;
  moveDisplacements[2] = 10;

  for (idx1 = 0; idx1 < 3; idx1 += 1) {
    checkSquare120 = square120 + moveDisplacements[idx1];

    for (idx2 = 0; idx2 < 10; idx2 += 1) {
      if (cBoard->pieces[checkSquare120] == NO_SQ) break;
      if ((cBoard->pieces[checkSquare120] >= wP) && (cBoard->pieces[checkSquare120] <= wK)) break;
      if ((cBoard->pieces[checkSquare120] == bR) || (cBoard->pieces[checkSquare120] == bQ)) return 1;
      if ((cBoard->pieces[checkSquare120] >= bP) && (cBoard->pieces[checkSquare120] <= bK)) break;

      checkSquare120 += moveDisplacements[idx1];
    }
  }

  // 4. Are diagonal sliding black pieces attacking?
  moveDisplacements[0] = 9;
  moveDisplacements[1] = 11;

  for (idx1 = 0; idx1 < 2; idx1 += 1) {
    checkSquare120 = square120 + moveDisplacements[idx1];

    for (idx2 = 0; idx2 < 10; idx2 += 1) {
      if (cBoard->pieces[checkSquare120] == NO_SQ) break;
      if ((cBoard->pieces[checkSquare120] >= wP) && (cBoard->pieces[checkSquare120] <= wK)) break;
      if ((cBoard->pieces[checkSquare120] == bB) || (cBoard->pieces[checkSquare120] == bQ)) return 1;
      if ((cBoard->pieces[checkSquare120] >= bP) && (cBoard->pieces[checkSquare120] <= bK)) break;

      checkSquare120 += moveDisplacements[idx1];
    }
  }

  // 5. Is black king attacking?
  if (cBoard->pieces[square120 + 1] == bK) return 1;
  if (cBoard->pieces[square120 - 1] == bK) return 1;
  if (cBoard->pieces[square120 + 9] == bK) return 1;
  if (cBoard->pieces[square120 + 10] == bK) return 1;
  if (cBoard->pieces[square120 + 11] == bK) return 1;

  return 0;
}

void moveGen_white_king_castle_king_side(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if (CHECK_BIT(cBoard->castlingPerm, WKCastling) == 0) return;

  // King is on E1 square. Check that squares between him and the king side rook are empty.
  if (cBoard->pieces[F1] != EMPTY) return;
  if (cBoard->pieces[G1] != EMPTY) return;

  // Check that kings square, square where he will pass, and his new squares are not attacked.
  if (check_white_castling_path_for_attacked_squares(cBoard, E1) == 1) return;
  if (check_white_castling_path_for_attacked_squares(cBoard, F1) == 1) return;
  if (check_white_castling_path_for_attacked_squares(cBoard, G1) == 1) return;

  // If we got to this point, then we can make a king side castle move.
  move = 0ULL;

  move |= (0ULL | square120);
  move |= (0ULL | G1) << 8;
  move |= (0ULL | wK) << 16;

  SET_BIT(move, MOVE_BIT_K_CASTLE);

  cBoard->moves[cBoard->movesAvailable] = move;
  cBoard->movesAvailable += 1;
}

void moveGen_white_king_castle_queen_side(BOARD *cBoard, unsigned char square120)
{
  unsigned long long move = 0ULL;

  if (CHECK_BIT(cBoard->castlingPerm, WQCastling) == 0) return;

  // King is on E1 square. Check that squares between him and the queen side rook are empty.
  if (cBoard->pieces[B1] != EMPTY) return;
  if (cBoard->pieces[C1] != EMPTY) return;
  if (cBoard->pieces[D1] != EMPTY) return;

  // Check that kings square, square where he will pass, and his new squares are not attacked.
  if (check_white_castling_path_for_attacked_squares(cBoard, E1) == 1) return;
  if (check_white_castling_path_for_attacked_squares(cBoard, D1) == 1) return;
  if (check_white_castling_path_for_attacked_squares(cBoard, C1) == 1) return;

  // If we got to this point, then we can make a queen side castle move.
  move = 0ULL;

  move |= (0ULL | square120);
  move |= (0ULL | C1) << 8;
  move |= (0ULL | wK) << 16;

  SET_BIT(move, MOVE_BIT_Q_CASTLE);

  cBoard->moves[cBoard->movesAvailable] = move;
  cBoard->movesAvailable += 1;
}

void moveGen_wB(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[4] = { -11, -9, 11, 9 };
  moveGen_white_sliding_piece(cBoard, square120, wB, &moveDisplacements, 4);
}

void moveGen_wR(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[4] = { -10, -1, 10, 1 };
  moveGen_white_sliding_piece(cBoard, square120, wR, &moveDisplacements, 4);
}

void moveGen_wQ(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[8] = { -11, -9, 11, 9, -10, -1, 10, 1 };
  moveGen_white_sliding_piece(cBoard, square120, wQ, &moveDisplacements, 8);
}

void moveGen_wK(BOARD *cBoard, unsigned char square120)
{
  unsigned char moveDisplacements[8] = { -11, -9, 11, 9, -10, -1, 10, 1 };
  moveGen_white_sliding_piece(cBoard, square120, wK, &moveDisplacements, 8);
  moveGen_white_king_castle_king_side(cBoard, square120);
  moveGen_white_king_castle_queen_side(cBoard, square120);
}
