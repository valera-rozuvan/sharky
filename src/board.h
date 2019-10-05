#ifndef __BOARD_H__
#define __BOARD_H__

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
  U8 castlingPerm;
  U8 enPassantSq;
  U8 fiftyMove;
  U64 positionKey;
} UNDO_MOVE;

typedef struct {
  U8 pieces[BOARD_SQ_NUM];

  // Pawn bit mask.
  //
  // 00000000
  // 00100000
  // 00000000
  // ...
  //
  // for all 64 chess board squares
  U64 pawns[3]; // white, black, both (all pawns together)

  // Squares on which the kings are on. White, black.
  U8 kingSq[2];

  // Castling permissions. Bit mask.
  // Can test against castling enums.
  // For example: 0100 means that only white king can castle queen side.
  U8 castlingPerm;

  // Current side to move.
  U8 side;

  // En passant square. If no en passant this move, set to NO_SQ.
  U8 enPassantSq;

  // Fifty move counter. When this hits 100, the game is a draw.
  // 100 - because we are using half moves, not full moves.
  U8 fiftyMove;

  // How many half moves are we in the current search.
  U8 ply;

  // How many half moves has been made in the game so far.
  unsigned int historyPly;

  // Current position hash. Unique key.
  U64 positionKey;

  // Number of pieces on the board. Indexed by piece type.
  // Remember, that index 0 is the EMPTY piece.
  U8 numPieces[13];

  // For evaluation. Number of pieces on the board.
  // 3 indexes - white, black, and both.
  //
  // Big pieces - anything that is not a pawn.
  // Major pieces - rooks and queens
  // Minor oieces - bishops and knights.
  U8 bigPieces[3];
  U8 majorPieces[3];
  U8 minorPieces[3];

  // Move history. Allows for undoing moves.
  // Store information about current board position, before
  // making a new move.
  UNDO_MOVE history[MAX_GAME_MOVES_NUM];
} BOARD;

#endif

