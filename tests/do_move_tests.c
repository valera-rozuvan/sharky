#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "../src/do_move.h"
#include "../src/move_gen.h"
#include "../src/fen.h"
#include "../src/board.h"
#include "../src/board_routines.h"
#include "../src/zobrist_hashing.h"

#include "zobrist_hashing_tests.h"
#include "tests.h"

unsigned char randomR(unsigned char min, unsigned char max)
{
  double x = (double)rand() / RAND_MAX;
  return (max - min + 1) * x + min;
}

void doMoveTests()
{
  BOARD cBoard;
  unsigned char randNum = 0;
  unsigned short repeatCount = 0;

  printf("Starting do_move_tests...\n");

  srand(time(0));

  for (repeatCount = 0; repeatCount < 16000; repeatCount += 1) {
    setupInitialPosition(&cBoard);
    moveGen(&cBoard);
    printBoard(&cBoard);
    printMoves(&cBoard);

    do {
      randNum = randomR(0, cBoard.movesAvailable - 1);
      doMove(&cBoard, cBoard.moves[randNum]);
      moveGen(&cBoard);
      printBoard(&cBoard);
      printMoves(&cBoard);
    } while ((cBoard.movesAvailable > 0) && (cBoard.fiftyMove < 100));

    do {
      undoMove(&cBoard);
    } while (cBoard.historyPly > 0);

    if (generateFullHash(&cBoard) != INITIAL_POSITION_ZOBRIST_KEY) {
      printf("After undoing all moves, starting position is invalid!\n");
      exit(1);
    }

    totalChecksPerformed += 1;
  }

  printf("Done!\n\n");
}
