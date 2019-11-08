#include <stdio.h>

#include "board.h"
#include "board_routines.h"
#include "fen.h"
#include "move_gen.h"
#include "do_move.h"

void human()
{
  BOARD cBoard;

  setupInitialPosition(&cBoard);
  moveGen(&cBoard);
  printBoard(&cBoard);
  printMoves(&cBoard);
}
