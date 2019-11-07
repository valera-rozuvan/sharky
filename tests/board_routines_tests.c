#include <stdlib.h>
#include <stdio.h>

#include "../src/defs.h"
#include "../src/board_routines.h"

#include "tests.h"

void board_routines_tests()
{
  unsigned char idx = 0;

  printf("Starting board_routines_tests...\n");

  for (idx = 0; idx < 64; idx += 1) {
    if (board64to120[idx] >= 120) {
      printf("board64to120[idx] >= 120; idx = %hhu\n", idx);
      printf("board64to120[idx] = %hhu\n", board64to120[idx]);

      exit(1);
    } else {
      totalChecksPerformed += 1;
    }
  }

  for (idx = 0; idx < 120; idx += 1) {
    if ((board120to64[idx] >= 64) && (board120to64[idx] != NO_SQ)) {
      printf("(board120to64[idx] >= 64) && (board120to64[idx] != NO_SQ); idx = %hhu\n", idx);
      printf("board120to64[idx] = %hhu\n", board120to64[idx]);

      exit(1);
    } else {
      totalChecksPerformed += 1;
    }
  }

  for (idx = 0; idx < 64; idx += 1) {
    if (board120to64[board64to120[idx]] != idx) {
      printf("board120to64[board64to120[idx]] != idx; idx = %hhu\n", idx);
      printf("board64to120[idx] = %hhu\n", board64to120[idx]);
      printf("board120to64[board64to120[idx]] = %hhu\n", board120to64[board64to120[idx]]);

      exit(1);
    } else {
      totalChecksPerformed += 1;
    }
  }

  printf("Done!\n\n");
}
