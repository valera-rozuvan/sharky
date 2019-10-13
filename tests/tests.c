#include "../src/vassert.h"

#include "random_const_tests.h"
#include "board_routines_tests.h"
#include "bitboard_tests.h"

int main()
{
  VASSERT_TEST();

  random_const_tests();
  board_routines_tests();
  bitboard_tests();

  return 0;
}
