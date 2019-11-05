#include <stdio.h>

#include "../src/board.h"
#include "../src/board_routines.h"
#include "../src/bitboard.h"
#include "../src/move_gen.h"
#include "../src/do_move.h"
#include "../src/fen.h"

unsigned long long countMoves(BOARD *cBoard, unsigned char bailout)
{
  unsigned long long count = 0;
  unsigned idx = 0;

  moveGen(cBoard);
  removeIllegalMoves(cBoard);

  if (bailout == 0) {
    count = cBoard->legalMovesAvailable;
  } else if ((cBoard->legalMovesAvailable == 0) || (cBoard->fiftyMove >= 100) || (checkDrawByRepetition(cBoard) == 1)) {
    count = 0;
  } else {
    for (idx = 0; idx < cBoard->movesAvailable; idx += 1) {
      if (CHECK_BIT(cBoard->moves[idx], MOVE_BIT_ILLEGAL) == 1) {
        continue;
      }

      doMove(cBoard, cBoard->moves[idx]);
      count += countMoves(cBoard, bailout - 1);
      undoMove(cBoard);

      moveGen(cBoard);
      removeIllegalMoves(cBoard);
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

  printf("%s\n", perftPos);
  setPositionFromFen(&cBoard, perftPos);
  // printBoard(&cBoard);

  for (bailout = 0; bailout < 6; bailout += 1) {
    count = countMoves(&cBoard, bailout);
    printf("depth %hhu: perft count = %llu\n", bailout + 1, count);
  }

  return 0;
}
