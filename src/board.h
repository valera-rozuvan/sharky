#ifndef __BOARD_H__
#define __BOARD_H__

#include "defs.h"

/*
 * Information used to undo a move.
 * This will allow to revert a board to a previous
 * state, before the move was made.
 *
 * Store all critical knowledge about the state of the
 * game before the move.
 */
typedef struct {
  // The actual move being played.
  int move;

  // All below properties are part of the board state.
  unsigned char castlingPerm;
  unsigned char enPassantFile;
  unsigned char fiftyMove;

  unsigned long long positionKey;
} UNDO_MOVE;

typedef struct {
  unsigned char pieces[120];

  // Pawn bit mask.
  //
  // 00000000
  // 00100000
  // 00000000
  // ...
  //
  // for all 64 chess board squares
  unsigned long long pawns[3]; // white, black, both (all pawns together)

  // Squares on which the kings are on. White, black.
  unsigned char kingSq[2];

  // Castling permissions. Bit mask.
  // Can test against castling enums.
  // For example: 0100 means that only white king can castle queen side.
  unsigned char castlingPerm;

  // Current side to move.
  unsigned char side;

  // En passant file. If no en passant capture available, set to NO_EN_PASSANT.
  unsigned char enPassantFile;

  // Fifty move counter. When this hits 100, the game is a draw.
  // 100 - because we are using half moves, not full moves.
  unsigned char fiftyMove;

  // How many half moves are we in the current search.
  unsigned char searchPly;

  // How many half moves has been made in the game so far.
  unsigned int historyPly;

  // Current position hash. Unique key.
  unsigned long long positionKey;

  // Number of pieces on the board. Indexed by piece type.
  // Remember, that index 0 is the EMPTY piece.
  unsigned char numPieces[13];

  // Where exactly are pieces on the board. For each color/type
  // of piece. Remember, that index 0 is the EMPTY piece. If you promote
  // all pawns to one type of piece, maximum can be 10.
  // Why? So that we don't for loop over all 64 squares to find pieces.
  unsigned char pieceList[13][10];

  // For evaluation. Number of pieces on the board.
  // 3 indexes - white, black, and both.
  //
  // Big pieces - anything that is not a pawn.
  // Major pieces - rooks and queens
  // Minor pieces - bishops and knights.
  unsigned char bigPieces[3];
  unsigned char majorPieces[3];
  unsigned char minorPieces[3];

  unsigned long long moves[MAX_POSSIBLE_MOVES_IN_POSITION];
  unsigned char movesAvailable;

  // Move history. Allows for undoing moves.
  // Store information about current board position, before
  // making a new move.
  UNDO_MOVE history[MAX_GAME_MOVES_NUM];
} BOARD;

#endif // __BOARD_H__
