#include <stdlib.h>
#include <stdio.h>

#include "../src/defs.h"
#include "../src/fen.h"
#include "../src/board.h"
#include "../src/board_routines.h"

#include "perft_tests.h"
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

void checkErrorResultForFen(
  unsigned char expectedError, const char testFenStr[], const char testErrorMessage[],
  unsigned char drawBoard, unsigned long long expectedPositionKey
)
{
  BOARD cBoard;
  unsigned char result = 0;

  result = setPositionFromFen(&cBoard, testFenStr);

  if (drawBoard == 1) {
    printBoard(&cBoard);

    if (cBoard.positionKey != expectedPositionKey) {
      printf("%s\n", testErrorMessage);
      exit(1);
    }
  }

  if (result != expectedError) {
    printf("%s\n", testErrorMessage);
    exit(1);
  } else {
    totalChecksPerformed += 1;
  }
}

void fenPerftTests()
{
  char testErrorMessage[100];
  unsigned char idx = 0;

  for (idx = 0; idx < PEFRT_FEN_STRINGS_LENGTH; idx += 1) {
    snprintf(testErrorMessage, 36, "Valid perft FEN #%hhu should pass.", idx + 1);

    checkErrorResultForFen(
      0,
      PEFRT_FEN_STRINGS[idx],
      testErrorMessage,
      0, 0
    );
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
    1, 0xef03a45ed3c2355fULL
  );
  checkErrorResultForFen(
    1,
    "",
    "Empty FEN string should not pass FEN validation.",
    0, 0
  );
  checkErrorResultForFen(
    2,
    "rnbqkbnr/ppppp^&RTy7t7&*8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "FEN string with invalid symbols should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    3,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
    "FEN string with missing data should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    4,
    "rnbqkbnr/ppppppppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "FEN with too many files should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    4,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/RNBQKBNR w KQkq - 0 1",
    "FEN with too many ranks should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    5,
    "rnbqkbnr/pppppppp/8/8/8/7w/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "FEN with invalid pieces symbols should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    6,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBN w KQkq - 0 1",
    "FEN with too few piece symbols in 1st rank should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    6,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP w KQkq - 0 1",
    "FEN with too few ranks should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    7,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ",
    "FEN which ends prematurely with a space after piece info should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    8,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR K KQkq - 0 1",
    "FEN with invalid symbol for side to move should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    9,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w",
    "FEN which ends prematurely after side to move should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    9,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w/KQkq - 0 1",
    "FEN without a space after side to move should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    10,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w ",
    "FEN which ends prematurely with a space after side to move should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    10,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq",
    "FEN which ends after castling perm should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    11,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w rQkq - 0 1",
    "FEN with invalid castling perm symbols should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    12,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w -Qkq - 0 1",
    "FEN with dash symbol in castling perm should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    13,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ",
    "FEN without en passant information should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    14,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq K3 0 1",
    "FEN without valid en passant file symbol should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    15,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq a",
    "FEN without en passant rank symbol should NOT pass.",
    0, 0
  );
  checkErrorResultForFen(
    16,
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq aq",
    "FEN without valid en passant rank symbol should NOT pass.",
    0, 0
  );

  fenPerftTests();

  printf("Done!\n\n");
}
