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

  // How many half moves has been made in the game so far.
  unsigned short historyPly;

  // Current position hash. Unique key.
  unsigned long long positionKey;

  // Number of pieces on the board. Indexed by piece type.
  // Remember, that index 0 is the EMPTY piece.
  unsigned char numPieces[13];

  unsigned long long moves[MAX_POSSIBLE_MOVES_IN_POSITION];
  unsigned char movesAvailable;

  // Move history. Allows for undoing moves.
  // Store information about current board position, before
  // making a new move.
  UNDO_MOVE history[MAX_GAME_MOVES_NUM];
} BOARD;

#endif // __BOARD_H__
