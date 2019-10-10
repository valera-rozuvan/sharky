#include <stdio.h>

#include "vassert.h"
#include "defs.h"
#include "board.h"
#include "board_routines.h"
#include "bitboard.h"

int main()
{
  initBitMasks();

  VASSERT_TEST();
  initBoardCoordConvArrays();
  printBoardCoordConvArrays();
  VASSERT_U_CHAR_EQ(board64to120[13], 36);
  VASSERT_U_CHAR_EQ(board120to64[42], 17);

  unsigned long long bBoard = 0ULL;
  bBoard |= (1ULL << board120to64[D2]);
  bBoard |= (1ULL << board120to64[G7]);
  printBoard64(bBoard);

  unsigned char bitCount = count_1s(bBoard);
  printf("bit count = %hhu\n\n", bitCount);

  unsigned char poppedBit = pop_1st_bit(&bBoard);
  printf("popped bit = %hhu\n\n", poppedBit);

  printBoard64(bBoard);

  printf("Clearing G7...\n\n");
  CLEAR_BIT(bBoard, board120to64[G7]);
  printBoard64(bBoard);

  printf("Setting H7...\n\n");
  SET_BIT(bBoard, board120to64[H7]);
  printBoard64(bBoard);

  return 0;
}

