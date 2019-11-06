#include <stdio.h>

#include "../src/board.h"
#include "../src/board_routines.h"
#include "../src/bitboard.h"
#include "../src/move_gen.h"
#include "../src/do_move.h"
#include "../src/fen.h"

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
  }

  for (idx = 0; idx < cBoard->movesAvailable; idx += 1) {
    movesCopy[idx] = cBoard->moves[idx];
  }
  movesAvailableCopy = cBoard->movesAvailable;

  if (bailout == 0) {
    count = cBoard->legalMovesAvailable;
  } else if ((cBoard->legalMovesAvailable == 0) || (cBoard->fiftyMove >= 100) || (checkDrawByRepetition(cBoard) == 1)) {
    count = 0;
  } else {
    for (idx = 0; idx < movesAvailableCopy; idx += 1) {
      if (CHECK_BIT(movesCopy[idx], MOVE_BIT_ILLEGAL)) {
        continue;
      }

      doMove(cBoard, movesCopy[idx]);
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

int main()
{
  BOARD cBoard;
  unsigned long long count = 0ULL;
  unsigned char bailout = 0;

  char *perftPos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  // char *perftPos = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";
  // char *perftPos = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -";
  // char *perftPos = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
  // char *perftPos = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
  // char *perftPos = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";

  printf("%s\n", perftPos);
  setPositionFromFen(&cBoard, perftPos);

  for (bailout = 0; bailout < 6; bailout += 1) {
    count = countMoves(&cBoard, bailout, 0);
    printf("depth %hhu: perft count = %llu\n", bailout + 1, count);
  }

  return 0;
}
