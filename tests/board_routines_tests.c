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
      fprintf(stderr, "ERROR: board64to120[idx] >= 120; idx = %hhu\n", idx);
      fprintf(stderr, "ERROR: board64to120[idx] = %hhu\n", board64to120[idx]);
      exit(EXIT_FAILURE);
    } else {
      totalChecksPerformed += 1;
    }
  }

  for (idx = 0; idx < 120; idx += 1) {
    if ((board120to64[idx] >= 64) && (board120to64[idx] != NO_SQ)) {
      fprintf(stderr, "ERROR: (board120to64[idx] >= 64) && (board120to64[idx] != NO_SQ); idx = %hhu\n", idx);
      fprintf(stderr, "ERROR: board120to64[idx] = %hhu\n", board120to64[idx]);
      exit(EXIT_FAILURE);
    } else {
      totalChecksPerformed += 1;
    }
  }

  for (idx = 0; idx < 64; idx += 1) {
    if (board120to64[board64to120[idx]] != idx) {
      fprintf(stderr, "ERROR: board120to64[board64to120[idx]] != idx; idx = %hhu\n", idx);
      fprintf(stderr, "ERROR: board64to120[idx] = %hhu\n", board64to120[idx]);
      fprintf(stderr, "ERROR: board120to64[board64to120[idx]] = %hhu\n", board120to64[board64to120[idx]]);
      exit(EXIT_FAILURE);
    } else {
      totalChecksPerformed += 1;
    }
  }

  printf("Done!\n\n");
}
