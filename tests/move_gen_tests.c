#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../src/defs.h"
#include "../src/fen.h"
#include "../src/board.h"
#include "../src/board_routines.h"
#include "../src/move_gen.h"

#include "tests.h"

#define FEN_POS_TO_CHECK_LENGTH 14
#define MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK 17
const char *fenPosToCheck[FEN_POS_TO_CHECK_LENGTH] = {
  // *******************************************
  // White king side castling. Various threats.
  // *******************************************

  // No threats - king can castle.
  "4k3/8/8/8/8/8/8/4K2R w K - 0 1",

  // Knight is only threatening the rook. King can castle.
  "4k3/8/8/8/8/8/5n2/4K2R w K - 0 1",

  // In all below positions the king can't castle - since attacked by knight.
  "4k3/8/8/8/8/8/2n5/4K2R w K - 0 1",
  "4k3/8/8/8/8/3n4/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/5n2/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/8/6n1/4K2R w K - 0 1",

  // In all below positions the king can't castle - since passing square is attacked by knight.
  "4k3/8/8/8/8/8/3n4/4K2R w K - 0 1",
  "4k3/8/8/8/8/4n3/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/6n1/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/8/7n/4K2R w K - 0 1",

  // In all below positions the king can't castle - since finishing square is attacked by knight.
  "4k3/8/8/8/8/8/4n3/4K2R w K - 0 1",
  "4k3/8/8/8/8/5n2/8/4K2R w K - 0 1",
  "4k3/8/8/8/8/7n/8/4K2R w K - 0 1",

  // *******************************************
  // White queen side castling.
  "4k3/8/8/8/8/8/8/R3K3 w Q - 0 1"
};
const char *movesToCheckForPos[FEN_POS_TO_CHECK_LENGTH][MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK] = {
  // *******************************************
  // White king side castling. Various night threats.
  // *******************************************

  // No threats - king can castle.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "0-0", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // Knight is only threatening the rook. King can castle.
  { "e1d1", "e1d2", "e1e2", "e1xf2", "e1f1", "0-0", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // In all below positions the king can't castle - since attacked by knight.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },

  // In all below positions the king can't castle - since passing square is attacked by knight.
  { "e1d1", "e1xd2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1xh2", NULL },

  // In all below positions the king can't castle - since finishing square is attacked by knight.
  { "e1d1", "e1d2", "e1xe2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1h3", "h1h4", "h1h5", "h1h6", "h1h7", "h1h8", NULL },
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "h1g1", "h1f1", "h1h2", "h1xh3", NULL },

  // *******************************************
  // White queen side castling.
  { "e1d1", "e1d2", "e1e2", "e1f2", "e1f1", "0-0-0", "a1b1", "a1c1", "a1d1", "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8", NULL }
};

unsigned char arrayOfStrContainsStr(const char **hayStack, unsigned char hayStackSize, const char *needle)
{
  unsigned char idx = 0;

  do {
    if (hayStack[idx] == NULL) {
      return 0;
    }

    if (strcmp(hayStack[idx], needle) == 0) {
      return 1;
    }

    idx += 1;
  } while (idx < hayStackSize);

  return 0;
}

void testFenPos(BOARD *cBoard, const char *fenPos, const char *movesToCheck[])
{
  unsigned char idx = 0;

  char **generatedMoves = NULL;
  unsigned char generatedMovesNum = 0;

  generatedMovesNum = cBoard->movesAvailable;
  generatedMoves = malloc(generatedMovesNum * sizeof(char*));
  for (idx = 0; idx < generatedMovesNum; idx += 1) {
    generatedMoves[idx] = malloc((MAX_MOVE_STR_LENGTH + 1) * sizeof(char));
    chessMoveToStr(cBoard->moves[idx], generatedMoves[idx]);
  }

  for (idx = 0; idx < MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK; idx += 1) {
    if (movesToCheck[idx] == NULL) {
      break;
    }

    if (arrayOfStrContainsStr((const char**)generatedMoves, generatedMovesNum, movesToCheck[idx]) == 0) {
      printf("Move generation for FEN '%s' failed!\n", fenPos);
      printf("Move not generated: %s\n", movesToCheck[idx]);
      exit(1);
    }

    totalChecksPerformed += 1;
  }

  for (idx = 0; idx < generatedMovesNum; idx += 1) {
    if (arrayOfStrContainsStr(movesToCheck, MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK, generatedMoves[idx]) == 0) {
      printf("Move generation for FEN '%s' failed!\n", fenPos);
      printf("Generated move is unexpected: %s\n", generatedMoves[idx]);
      exit(1);
    }

    totalChecksPerformed += 1;
  }

  for (idx = 0; idx < generatedMovesNum; idx += 1) {
    free(generatedMoves[idx]);
  }
  free(generatedMoves);
}

void moveGenTests()
{
  BOARD cBoard;
  unsigned short idx = 0;

  printf("Starting move_gen_tests...\n");

  for (idx = 0; idx < FEN_POS_TO_CHECK_LENGTH; idx += 1) {
    setPositionFromFen(&cBoard, fenPosToCheck[idx]);
    moveGen(&cBoard);
    printBoard(&cBoard);
    printMoves(&cBoard);

    testFenPos(&cBoard, fenPosToCheck[idx], movesToCheckForPos[idx]);
  }

  printf("Done!\n\n");
}
