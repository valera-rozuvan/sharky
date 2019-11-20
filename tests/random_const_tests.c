#include <stdlib.h>
#include <stdio.h>

#include "../src/random_const.h"

#include "tests.h"

void random_const_tests()
{
  unsigned short idx1 = 0;
  unsigned short idx2 = 0;

  printf("Starting random_const_tests...\n");

  for (idx1 = 0; idx1 < RANDOM_CONST_LENGTH; idx1 += 1) {
    for (idx2 = idx1 + 1; idx2 < RANDOM_CONST_LENGTH; idx2 += 1) {
      if (RANDOM_CONST[idx1] == RANDOM_CONST[idx2]) {
        fprintf(stderr, "ERROR: Random number collision detected!\n");
        fprintf(stderr, "ERROR: idx1 = %hu, RANDOM_CONST[idx1] = %llu\n", idx1, RANDOM_CONST[idx1]);
        fprintf(stderr, "ERROR: idx2 = %hu, RANDOM_CONST[idx2] = %llu\n", idx2, RANDOM_CONST[idx2]);
        exit(EXIT_FAILURE);
      } else {
        totalChecksPerformed += 1;
      }
    }
  }

  printf("Done!\n\n");
}
