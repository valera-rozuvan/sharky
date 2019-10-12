#include <stdlib.h>
#include <stdio.h>

#include "../src/vassert.h"
#include "../src/defs.h"
#include "../src/board_routines.h"

void board_routines_tests()
{
  unsigned char idx = 0;

  for (idx = 0; idx < 64; idx += 1) {
    if (board64to120[idx] >= 120) {
      printf("board64to120[idx] >= 120; idx = %hhu\n", idx);
      printf("board64to120[idx] = %hhu\n", board64to120[idx]);

      exit(1);
    }
  }

  for (idx = 0; idx < 120; idx += 1) {
    if ((board120to64[idx] >= 64) && (board120to64[idx] != NO_SQ)) {
      printf("(board120to64[idx] >= 64) && (board120to64[idx] != NO_SQ); idx = %hhu\n", idx);
      printf("board120to64[idx] = %hhu\n", board120to64[idx]);

      exit(1);
    }
  }

  for (idx = 0; idx < 64; idx += 1) {
    if (board120to64[board64to120[idx]] != idx) {
      printf("board120to64[board64to120[idx]] != idx; idx = %hhu\n", idx);
      printf("board64to120[idx] = %hhu\n", board64to120[idx]);
      printf("board120to64[board64to120[idx]] = %hhu\n", board120to64[board64to120[idx]]);

      exit(1);
    }
  }

  VASSERT_U_CHAR_EQ(board64to120[13], 36);
  VASSERT_U_CHAR_EQ(board120to64[42], 17);
}

