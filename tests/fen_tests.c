#include <stdlib.h>
#include <stdio.h>

#include "../src/fen.h"
#include "../src/board.h"

#include "tests.h"

void emptyFenStrTest()
{
  BOARD cBoard;
  const char testFenStr[1] = "";
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
  const char testFenStr[256] = "VYpQLF2mYJ6IYC0Wdb7IaXwEq8lIHDqC5GRhi79xAyqKncUUSuCBH3QV5JhhJ9iwHSVqI8yeClq8Qhn7QN4ExbOeQLLZza21Twz6bffVK0i8I4oHkglK5xhU0ooNKKYGfOHHnOWgedsqjkh0kJdsjPeJ16o2nnIl74EblCL0qQ952amx0t5Rzt4dGgWBZENeC63JdqtynTSbrTSeS2YevyTVDiBCVBgCK23v6uebzggwQzpA89FLHL0k6FOtQiM";
  unsigned char result = 0;

  result = setPositionFromFen(&cBoard, testFenStr);

  if (result != 1) {
    printf("Very long FEN string should not pass FEN validation.\n");
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

  printf("Done!\n\n");
}
