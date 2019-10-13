#include "board.h"
#include "board_routines.h"
#include "random_const.h"
#include "bitboard.h"

const short randomConstArrOffset_piece[13] = {
  0,   // EMPTY - we don't care.

  -8,  // wP - gets indexes   0 -  47 (total 48)
  48,  // wN - gets indexes  48 - 111 (total 64)
  112, // wB - gets indexes 112 - 175 (total 64)
  176, // wR - gets indexes 176 - 239 (total 64)
  240, // wQ - gets indexes 240 - 303 (total 64)
  304, // wK - gets indexes 304 - 367 (total 64)

  360, // bP - gets indexes 368 - 415 (total 48)
  416, // bN - gets indexes 416 - 479 (total 64)
  480, // bB - gets indexes 480 - 543 (total 64)
  544, // bR - gets indexes 544 - 607 (total 64)
  608, // bQ - gets indexes 608 - 671 (total 64)
  672  // bK - gets indexes 672 - 735
};

const short randomConstArrOffset_side = 736;

const short randomConstArrOffset_castling[4] = {
  737, // WKCastling
  738, // WQCastling
  739, // BKCastling
  740  // BQCastling
};

const short randomConstArrOffset_enPassant[8] = {
  741, // FILE_A
  742, // FILE_B
  743, // FILE_C
  744, // FILE_D
  745, // FILE_E
  746, // FILE_F
  747, // FILE_G
  748  // FILE_H
};

unsigned long long generateFullHash(BOARD *cBoard)
{
  unsigned char idx = 0;
  unsigned char piece = 0;
  unsigned short randomConstArrIdx = 0;

  unsigned long long positionHash = 0ULL;

  // Pieces and their position.
  for (idx = 0; idx < 64; idx += 1) {
    piece = cBoard->pieces[board64to120[idx]];

    if (piece == EMPTY) {
      continue;
    }

    randomConstArrIdx = randomConstArrOffset_piece[piece] + idx;
    positionHash ^= RANDOM_CONST[randomConstArrIdx];
  }

  // Side to move.
  if (cBoard->side == BLACK) {
    positionHash ^= RANDOM_CONST[randomConstArrOffset_side];
  }

  // Castling rights.
  if (CHECK_BIT(cBoard->castlingPerm, WKCastling)) {
    positionHash ^= RANDOM_CONST[randomConstArrOffset_castling[WKCastling]];
  }
  if (CHECK_BIT(cBoard->castlingPerm, WQCastling)) {
    positionHash ^= RANDOM_CONST[randomConstArrOffset_castling[WQCastling]];
  }
  if (CHECK_BIT(cBoard->castlingPerm, BKCastling)) {
    positionHash ^= RANDOM_CONST[randomConstArrOffset_castling[BKCastling]];
  }
  if (CHECK_BIT(cBoard->castlingPerm, BQCastling)) {
    positionHash ^= RANDOM_CONST[randomConstArrOffset_castling[BQCastling]];
  }

  // En passant capture file, if available.
  if (cBoard->enPassantFile != NO_EN_PASSANT) {
    positionHash ^= RANDOM_CONST[randomConstArrOffset_enPassant[cBoard->enPassantFile]];
  }

  return positionHash;
}
