#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/board.h"
#include "../src/board_routines.h"
#include "../src/bitboard.h"
#include "../src/move_gen.h"
#include "../src/do_move.h"
#include "../src/fen.h"
#include "../src/zobrist_hashing.h"

#include "parse_options.h"

unsigned long long countMoves(BOARD *cBoard, unsigned char bailout, unsigned char printInfo)
{
  char fmtdMove[MAX_MOVE_STR_LENGTH] = "";

  unsigned long long movesCopy[MAX_POSSIBLE_MOVES_IN_POSITION];
  unsigned char movesAvailableCopy = 0;

  unsigned long long count = 0;
  unsigned long long countForMove = 0;
  unsigned idx = 0;

  moveGen(cBoard);
  removeIllegalMoves(cBoard);

  if (printInfo == 1) {
    printBoard(cBoard);
    printMoves(cBoard);
    printf("\n");
  }

  if (bailout == 1) {
    count = cBoard->legalMovesAvailable;
  } else if ((cBoard->legalMovesAvailable == 0) || (cBoard->fiftyMove >= 100) || (checkDrawByRepetition(cBoard) == 1)) {
    count = 0;
  } else {
    for (idx = 0; idx < cBoard->movesAvailable; idx += 1) {
      movesCopy[idx] = cBoard->moves[idx];
    }
    movesAvailableCopy = cBoard->movesAvailable;

    for (idx = 0; idx < movesAvailableCopy; idx += 1) {
      if (CHECK_BIT(movesCopy[idx], MOVE_BIT_ILLEGAL)) {
        continue;
      }

      doMove(cBoard, movesCopy[idx]);
      cBoard->positionKey = generateFullHash(cBoard);
      countForMove = countMoves(cBoard, bailout - 1, 0);
      count += countForMove;
      undoMove(cBoard);

      if (printInfo == 1) {
        chessMoveToStr(movesCopy[idx], fmtdMove);
        printf("%s: %llu\n", fmtdMove, countForMove);
      }
    }
  }

  return count;
}

int main(int argc, char *argv[])
{
  BOARD cBoard;
  unsigned long long count = 0ULL;
  unsigned char idx = 0;
  char *param = NULL;
  unsigned char perftDepth = 0;
  char *perftPos = NULL;

  setvbuf(stdout, NULL, _IONBF, 0);

  for (idx = 0; idx < argc; idx += 1) {
    param = argv[idx];

    if ((strcmp(param, "--depth") == 0) || (strcmp(param, "-d") == 0)) {
      perftDepth = parseDepthOption(argc, argv, idx);
    } else if ((strcmp(param, "--fen") == 0) || (strcmp(param, "-f") == 0)) {
      perftPos = parseFENOption(argc, argv, idx);

      if (setPositionFromFen(&cBoard, perftPos) != 0) {
        perftPos = NULL;
      }
    }
  }

  if (perftDepth == 0) {
    printf("Exiting... please provide a valid depth.\n");

    exit(EXIT_FAILURE);
    return 1;
  } else if (perftPos == NULL) {
    printf("Exiting... please provide a valid FEN string.\n");

    exit(EXIT_FAILURE);
    return 1;
  }

  printf("%s\n", perftPos);
  count = countMoves(&cBoard, perftDepth, 1);
  printf("\ndepth: %hhu; perft: %llu\n\n", perftDepth, count);

  exit(EXIT_SUCCESS);
  return 0;
}
