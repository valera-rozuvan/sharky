#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../src/get_real_time.h"

#include "random_const_tests.h"
#include "board_routines_tests.h"
#include "bitboard_tests.h"
#include "zobrist_hashing_tests.h"
#include "fen_tests.h"
#include "perft_tests.h"
#include "move_gen_tests.h"
#include "do_move_tests.h"
#include "utils_tests.h"

#include "tests.h"

unsigned short totalChecksPerformed = 0;

int main()
{
  double startTime, endTime;

  srand(time(0));

  startTime = getRealTime();

  random_const_tests();
  board_routines_tests();
  bitboard_tests();
  zobrist_hashing_tests();
  fen_tests();
  move_gen_tests();
  do_move_tests();
  utils_tests();

  endTime = getRealTime();

  printf("Total checks performed: %hu\n", totalChecksPerformed);
  printf("Time taken: %f seconds\n", endTime - startTime);

  return 0;
}
