#include <stdio.h>

#include "board.h"
#include "board_routines.h"

int main()
{
  BOARD bBoard;

  printf("%s v%s\n\n%s\n%s\n\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_LICENSE, PROGRAM_COPYRIGHT);

  setupInitialPosition(&bBoard);
  printBoard(&bBoard);

  printf("Position hash: %llx\n", bBoard.positionKey);

  return 0;
}
