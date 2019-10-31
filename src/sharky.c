#include <stdio.h>

#include "board.h"
#include "board_routines.h"
#include "fen.h"
#include "move_gen.h"
#include "do_move.h"

int main()
{
  BOARD cBoard;

  printf("%s v%s\n\n%s\n%s\n\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_LICENSE, PROGRAM_COPYRIGHT);

  setupInitialPosition(&cBoard);
  moveGen(&cBoard);
  printBoard(&cBoard);
  printMoves(&cBoard);

  doMove(&cBoard, cBoard.moves[0]);
  moveGen(&cBoard);
  printBoard(&cBoard);
  printMoves(&cBoard);

  return 0;
}
