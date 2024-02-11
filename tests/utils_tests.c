#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void testStartsWithStr()
{
  if (!startsWithStr("This is a test!", "This is")) {
    fprintf(stderr, "ERROR: startsWithStr test 1 failed!\n");
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }

  if (startsWithStr("This is a test!", "This is a test!123456")) {
    fprintf(stderr, "ERROR: startsWithStr test 2 failed!\n");
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }

  if (startsWithStr("This is a test!", "null")) {
    fprintf(stderr, "ERROR: startsWithStr test 3 failed!\n");
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }

  if (startsWithStr("This is a test!", "")) {
    fprintf(stderr, "ERROR: startsWithStr test 4 failed!\n");
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }

  if (startsWithStr("", "This is a test!")) {
    fprintf(stderr, "ERROR: startsWithStr test 5 failed!\n");
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }

  if (startsWithStr("This is a test!", NULL)) {
    fprintf(stderr, "ERROR: startsWithStr test 6 failed!\n");
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }

  if (startsWithStr(NULL, "This is a test!")) {
    fprintf(stderr, "ERROR: startsWithStr test 7 failed!\n");
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }
}

void testStripStr_testCase(char *str1, char *str2)
{
  char *buffer = NULL;

  buffer = stripStr(str1);
  if (strcmp(buffer, str2) != 0) {
    fprintf(stderr, "ERROR: stripStr test failed! Expected '%s' but got '%s'.\n", str2, buffer);
    fprintf(stderr, "ERROR: string to strip was '%s'.\n", str1);

    free(buffer);
    exit(EXIT_FAILURE);
  }
  free(buffer);
  totalChecksPerformed += 1;
}

void testStripStr()
{
  testStripStr_testCase(" hello ", "hello");
  testStripStr_testCase("  hello  ", "hello");
  testStripStr_testCase("   hello   ", "hello");

  testStripStr_testCase("hello ", "hello");
  testStripStr_testCase("hello  ", "hello");
  testStripStr_testCase("hello   ", "hello");

  testStripStr_testCase(" hello", "hello");
  testStripStr_testCase("  hello", "hello");
  testStripStr_testCase("   hello", "hello");

  testStripStr_testCase(" hello world ", "hello world");

  testStripStr_testCase(" hello  world ", "hello world");
  testStripStr_testCase(" hello   world ", "hello world");
  testStripStr_testCase(" hello    world ", "hello world");

  testStripStr_testCase("  hello world ", "hello world");
  testStripStr_testCase("   hello world ", "hello world");
  testStripStr_testCase("    hello world ", "hello world");

  testStripStr_testCase(" hello world  ", "hello world");
  testStripStr_testCase(" hello world   ", "hello world");
  testStripStr_testCase(" hello world    ", "hello world");

  testStripStr_testCase("  hello  world  ", "hello world");
  testStripStr_testCase("   hello   world   ", "hello world");
  testStripStr_testCase("    hello    world    ", "hello world");

  testStripStr_testCase(" hello world ! ", "hello world !");
  testStripStr_testCase("    hello    world    !    ", "hello world !");

  testStripStr_testCase("", "");

  testStripStr_testCase("  ", "");
  testStripStr_testCase("   ", "");
  testStripStr_testCase("    ", "");

  // TODO: figure out why this is breaking.
  // testStripStr_testCase(NULL, "");
}

void utils_tests()
{
  printf("Starting utils_tests...\n");

  testRandR();
  testStartsWithStr();
  testStripStr();

  printf("Done!\n\n");
}
