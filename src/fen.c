#include "board.h"
#include "fen.h"

/*
 *
 * The below description of FEN is taken from Wikipedia:
 *
 *   https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 *
 * Forsyth–Edwards Notation (FEN) is a standard notation for describing a particular board position of a chess game.
 * The purpose of FEN is to provide all the necessary information to restart a game from a particular position.
 *
 * A FEN "record" defines a particular game position, all in one text line and using only the ASCII character set.
 *
 * A FEN record contains six fields. The separator between fields is a space. The fields are:
 *
 * 1. Piece placement (from White's perspective). Each rank is described, starting with rank 8 and ending with rank 1;
 *    within each rank, the contents of each square are described from file "a" through file "h". Following the
 *    Standard Algebraic Notation (SAN), each piece is identified by a single letter taken from the standard English
 *    names (pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K"). White pieces are
 *    designated using upper-case letters ("PNBRQK") while black pieces use lowercase ("pnbrqk"). Empty squares are
 *    noted using digits 1 through 8 (the number of empty squares), and "/" separates ranks.
 *
 * 2. Active color. "w" means White moves next, "b" means Black moves next.
 *
 * 3. Castling availability. If neither side can castle, this is "-". Otherwise, this has one or more
 *    letters: "K" (White can castle kingside), "Q" (White can castle queenside), "k" (Black can castle kingside),
 *    and/or "q" (Black can castle queenside).
 *
 * 4. En passant target square in algebraic notation. If there's no en passant target square, this is "-". If a pawn
 *    has just made a two-square move, this is the position "behind" the pawn. This is recorded regardless of whether
 *    there is a pawn in position to make an en passant capture.
 *
 * 5. Halfmove clock: This is the number of halfmoves since the last capture or pawn advance. This is used to determine
 *    if a draw can be claimed under the fifty-move rule.
 *
 * 6. Fullmove number: The number of the full move. It starts at 1, and is incremented after Black's move.
 *
 *
 * Examples:
 *
 * Here is the FEN for the starting position:
 *   rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
 *
 * Here is the FEN after the move 1. e4:
 *   rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
 *
 * And then after 1. ... c5:
 *   rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
 *
 * And then after 2. Nf3:
 *   rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2
 *
 */

#define ALLOWED_FEN_SYMBOLS_LENGTH 34
const char allowedFenSymbols[ALLOWED_FEN_SYMBOLS_LENGTH] = {
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
  '0', '1', '2', '3', '4', '5', '6', '7', '8',
  ' ', '/', '-',
  'P', 'N', 'B', 'R', 'Q', 'K',
  'p', 'n', 'b', 'r', 'q', 'k',
  'w', 'b'
};

unsigned char setPositionFromFen(BOARD *cBoard, const char *fenStr)
{
  unsigned char idx1 = 0;
  unsigned char idx2 = 0;

  for (idx1 = 0; idx1 < MAX_ALLOWED_FEN_STRING_LENGTH; idx1 += 1) {
    if (fenStr[idx1] == 0) {
      break;
    }
  }

  if ((idx1 == 0) || (idx1 == MAX_ALLOWED_FEN_STRING_LENGTH)) {
    return 1;
  }

  idx1 = 0;
  do {
    idx2 = 0;

    for (idx2 = 0; idx2 < ALLOWED_FEN_SYMBOLS_LENGTH; idx2 += 1) {
      if (fenStr[idx1] == allowedFenSymbols[idx2]) {
        break;
      }
    }

    if (idx2 == ALLOWED_FEN_SYMBOLS_LENGTH) {
      return 2;
    }

    idx1 += 1;
  } while (fenStr[idx1] != 0);

  cBoard->fiftyMove = 0;

  return 0;
}
