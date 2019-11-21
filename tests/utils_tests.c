#include <stdlib.h>
#include <stdio.h>

#include "../src/utils.h"

#include "tests.h"

#define NUM_ELEMENTS_RND_ARRAY 5

void testRandR()
{
  unsigned char randArr[NUM_ELEMENTS_RND_ARRAY] = { 0, 0, 0, 0, 0 };
  unsigned short idx = 0;

  for (idx = 0; idx < 1000; idx += 1) {
    randArr[randomR(0, NUM_ELEMENTS_RND_ARRAY - 1)] += 1;
  }

  for (idx = 0; idx < NUM_ELEMENTS_RND_ARRAY; idx += 1) {
    if (randArr[idx] == 0) {
      fprintf(stderr, "ERROR: randomR() does not cover the whole range from 0 to %hhu\n", NUM_ELEMENTS_RND_ARRAY - 1);
      exit(EXIT_FAILURE);
    }
  }

  totalChecksPerformed += 1;
}

void utils_tests()
{
  printf("Starting utils_tests...\n");

  testRandR();

  printf("Done!\n\n");
}
