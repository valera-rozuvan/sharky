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
#include "../src/utils.h"

#include "perft_tests.h"
#include "zobrist_hashing_tests.h"
#include "tests.h"

void playRandomGames(const char *perftPos)
{
  BOARD cBoard;
  unsigned char randNum = 0;
  unsigned short repeatCount = 0;
  unsigned long long initialPositionHash = 0ULL;

  for (repeatCount = 0; repeatCount < 1000; repeatCount += 1) {
    setPositionFromFen(&cBoard, perftPos);
    moveGen(&cBoard);
    printBoard(&cBoard);
    printMoves(&cBoard);

    initialPositionHash = cBoard.positionKey;

    do {
      randNum = randomR(0, cBoard.movesAvailable - 1);
      doMove(&cBoard, cBoard.moves[randNum]);
      cBoard.positionKey = generateFullHash(&cBoard);
      moveGen(&cBoard);
      printBoard(&cBoard);
      printMoves(&cBoard);
    } while ((cBoard.movesAvailable > 0) && (cBoard.fiftyMove < 100));

    do {
      undoMove(&cBoard);
      moveGen(&cBoard);
      printBoard(&cBoard);
      printMoves(&cBoard);
    } while (cBoard.historyPly > 0);

    if (generateFullHash(&cBoard) != initialPositionHash) {
      fprintf(stderr, "ERROR: After undoing all moves, starting position is invalid!\n");
      exit(EXIT_FAILURE);
    }

    totalChecksPerformed += 1;
  }
}

void doMoveTests()
{
  unsigned char idx = 0;

  printf("Starting do_move_tests...\n");

  srand(time(0));

  for (idx = 0; idx < PEFRT_FEN_STRINGS_LENGTH; idx += 1) {
    playRandomGames(PEFRT_FEN_STRINGS[idx]);
  }

  printf("Done!\n\n");
}
