#include <stdio.h>

#include "../src/vassert.h"

#include "random_const_tests.h"
#include "board_routines_tests.h"
#include "bitboard_tests.h"
#include "zobrist_hashing_tests.h"
#include "tests.h"

unsigned short totalChecksPerformed = 0;

int main()
{
  VASSERT_TEST();

  random_const_tests();
  board_routines_tests();
  bitboard_tests();
  zobrist_hashing_tests();

  printf("Total checks performed: %hu\n", totalChecksPerformed);

  return 0;
}
