#include <stdio.h>

#include "vassert.h"
#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "bitboard.h"

int main()
{
  VASSERT_TEST();
  initBoardCoordConvArrays();
  printBoardCoordConvArrays();
  VASSERT_U_CHAR_EQ(arr64to120[13], 36);
  VASSERT_U_CHAR_EQ(arr120to64[42], 17);

  U64 bBoard = 0ULL;
  bBoard |= (1ULL << arr120to64[D2]);
  bBoard |= (1ULL << arr120to64[G7]);
  printBitboard(bBoard);

  return 0;
}

