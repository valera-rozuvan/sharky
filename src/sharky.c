#include "vassert.h"

#include "defs.h"
#include "board.h"
#include "board_routines.h"

int main()
{
  VASSERT_TEST();
  initBoardCoordConvArrays();
  printBoardCoordConvArrays();
  VASSERT_U_CHAR_EQ(arr64to120[13], 36);
  VASSERT_U_CHAR_EQ(arr120to64[42], 17);

  return 0;
}

