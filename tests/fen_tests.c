#include <stdlib.h>
#include <stdio.h>

#include "../src/fen.h"
#include "../src/board.h"
#include "../src/board_routines.h"

#include "tests.h"

void emptyFenStrTest()
{
  BOARD cBoard;
  const char testFenStr[] = "";
  unsigned char result = 0;

  result = setPositionFromFen(&cBoard, testFenStr);

  if (result != 1) {
    printf("Empty FEN string should not pass FEN validation.\n");
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void veryLongFenStrTest()
{
  BOARD cBoard;
  char *testFenStr = NULL;
  unsigned char result = 0;
  unsigned char idx1 = 0;
  unsigned char testFenStrLength = MAX_ALLOWED_FEN_STRING_LENGTH + 1;

  // Size is plus 1 because last char in memory should be `\0` char.
  testFenStr = (char*)malloc(sizeof(char) * (testFenStrLength + 1));

  for (idx1 = 0; idx1 < testFenStrLength; idx1 += 1) {
    // Initialize string, because otherwise there will be random data, which can include
    // a prematurely placed `\0` char.
    testFenStr[idx1] = 'a';
  }
  testFenStr[testFenStrLength] = '\0';

  result = setPositionFromFen(&cBoard, testFenStr);
  free(testFenStr);

  if (result != 1) {
    printf("Very long FEN string should not pass FEN validation.\n");
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void validFenStringTest()
{
  BOARD cBoard;
  const char testFenStr[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  unsigned char result = 0;

  result = setPositionFromFen(&cBoard, testFenStr);

  printBoard(&cBoard);

  if (result != 0) {
    printf("Valid FEN string should pass.\n");
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void invalidSymbolsTest()
{
  BOARD cBoard;
  const char testFenStr[] = "rnbqkbnr/ppppp^&RTy7t7&*8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  unsigned char result = 0;

  result = setPositionFromFen(&cBoard, testFenStr);

  if (result != 2) {
    printf("FEN string with invalid symbols should NOT pass.\n");
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void stringWithMissingDataTest()
{
  BOARD cBoard;
  const char testFenStr[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  unsigned char result = 0;

  result = setPositionFromFen(&cBoard, testFenStr);

  if (result != 3) {
    printf("FEN string with missing data should NOT pass.\n");
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void fenTests()
{
  printf("Starting fen_tests...\n");

  emptyFenStrTest();
  veryLongFenStrTest();
  validFenStringTest();
  invalidSymbolsTest();
  stringWithMissingDataTest();

  printf("Done!\n\n");
}
