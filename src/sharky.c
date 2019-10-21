#include <stdio.h>

#include "board.h"
#include "board_routines.h"
#include "fen.h"

int main()
{
  BOARD cBoard;

  printf("%s v%s\n\n%s\n%s\n\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_LICENSE, PROGRAM_COPYRIGHT);

  setupInitialPosition(&cBoard);
  printBoard(&cBoard);

  return 0;
}
