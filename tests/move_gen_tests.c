#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../src/defs.h"
#include "../src/fen.h"
#include "../src/board.h"
#include "../src/board_routines.h"
#include "../src/move_gen.h"

#include "move_gen_data_tests.h"
#include "tests.h"

unsigned char arrayOfStrContainsStr(const char **hayStack, const unsigned char hayStackSize, const char *needle)
{
  unsigned char idx = 0;

  if (hayStackSize == 0) return 0;

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

void testFenPos(const BOARD *cBoard, const char *fenPos, const char **movesToCheck)
{
  unsigned char idx = 0;

  char **generatedMoves = NULL;
  unsigned char generatedMovesNum = 0;

  generatedMovesNum = cBoard->movesAvailable;
  generatedMoves = malloc(generatedMovesNum * sizeof(char*));
  for (idx = 0; idx < generatedMovesNum; idx += 1) {
    generatedMoves[idx] = malloc(MAX_MOVE_STR_LENGTH * sizeof(char));
    chessMoveToStr(cBoard->moves[idx], generatedMoves[idx]);
  }

  for (idx = 0; idx < MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK; idx += 1) {
    if (movesToCheck[idx] == NULL) {
      break;
    }

    if (arrayOfStrContainsStr((const char**)generatedMoves, generatedMovesNum, movesToCheck[idx]) == 0) {
      printf("Move generation for FEN '%s' failed!\n", fenPos);
      printf("Move not generated: %s\n", movesToCheck[idx]);
      exit(EXIT_FAILURE);
    }

    totalChecksPerformed += 1;
  }

  for (idx = 0; idx < generatedMovesNum; idx += 1) {
    if (arrayOfStrContainsStr(movesToCheck, MAX_POSSIBLE_MOVES_IN_POS_TO_CHECK, generatedMoves[idx]) == 0) {
      printf("Move generation for FEN '%s' failed!\n", fenPos);
      printf("Generated move is unexpected: %s\n", generatedMoves[idx]);
      exit(EXIT_FAILURE);
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
