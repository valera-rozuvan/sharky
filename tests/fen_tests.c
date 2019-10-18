#include <stdlib.h>
#include <stdio.h>

#include "../src/defs.h"
#include "../src/fen.h"
#include "../src/board.h"
#include "../src/board_routines.h"

#include "tests.h"

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

void checkErrorResultForFen(
  unsigned char expectedError, const char testFenStr[], const char testErrorMessage[], unsigned char drawBoard
)
{
  BOARD cBoard;
  unsigned char result = 0;

  result = setPositionFromFen(&cBoard, testFenStr);

  if (drawBoard == TRUE) {
    printBoard(&cBoard);
  }

  if (result != expectedError) {
    printf("%s\n", testErrorMessage);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void fenTests()
{
  printf("Starting fen_tests...\n");

  veryLongFenStrTest();

  checkErrorResultForFen(
    0,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "Valid FEN string should pass.",
    TRUE
  );
  checkErrorResultForFen(
    1,
    "",
    "Empty FEN string should not pass FEN validation.",
    FALSE
  );
  checkErrorResultForFen(
    2,
    "rnbqkbnr/ppppp^&RTy7t7&*8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "FEN string with invalid symbols should NOT pass.",
    FALSE
  );
  checkErrorResultForFen(
    3,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
    "FEN string with missing data should NOT pass.",
    FALSE
  );
  checkErrorResultForFen(
    4,
    "rnbqkbnr/ppppppppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "FEN with too many files should NOT pass.",
    FALSE
  );
  checkErrorResultForFen(
    4,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/RNBQKBNR w KQkq - 0 1",
    "FEN with too many ranks should NOT pass.",
    FALSE
  );
  checkErrorResultForFen(
    5,
    "rnbqkbnr/pppppppp/8/8/8/7w/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "FEN with invalid pieces symbols should NOT pass.",
    FALSE
  );
  checkErrorResultForFen(
    6,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBN w KQkq - 0 1",
    "FEN with too few piece symbols in 1st rank should NOT pass.",
    FALSE
  );
  checkErrorResultForFen(
    6,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP w KQkq - 0 1",
    "FEN with too few ranks should NOT pass.",
    FALSE
  );
  checkErrorResultForFen(
    7,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR K KQkq - 0 1",
    "FEN with invalid symbol for side to move should NOT pass.",
    FALSE
  );

  printf("Done!\n\n");
}
