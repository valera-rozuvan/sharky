#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "defs_arch.h"
#include "utils.h"
#include "board_routines.h"
#include "fen.h"
#include "move_gen.h"

#define READ_BUFFER_SIZE 8192

void uciOK()
{
  printf("id name %s %s %s\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_ARCH);
  printf("id author %s\n", PROGRAM_AUTHOR);
  printf("uciok\n");
}

void uci()
{
  BOARD cBoard;
  char *buffer = NULL, *readBuffer = NULL, rawBuffer[READ_BUFFER_SIZE] = "";

  setupInitialPosition(&cBoard);
  moveGen(&cBoard);

  uciOK();

  setbuf(stdout, NULL);

  do {
    if (fgets(rawBuffer, READ_BUFFER_SIZE, stdin) == NULL) {
      sleepMs(2);

      continue;
    }

    readBuffer = stripStr(rawBuffer);
    buffer = readBuffer;

    if (compareStrFF(&buffer, "isready")) {
      printf("readyok\n");
    } else if (compareStrFF(&buffer, "stop")) {
      // Always send the best move when engine stops searching.

      // TODO: Actually send the best move ;)
      printf("bestmove e2e4\n");
    } else if (compareStrFF(&buffer, "quit")) {
      break;
    } else if (compareStrFF(&buffer, "ucinewgame")) {
      setupInitialPosition(&cBoard);
      moveGen(&cBoard);
    } else if (compareStrFF(&buffer, "position fen")) {
      setPositionFromFen(&cBoard, buffer);
      moveGen(&cBoard);
    } else if (compareStrFF(&buffer, "print")) {
      printBoard(&cBoard);
    } else if (compareStrFF(&buffer, "uci")) {
      uciOK();
    }

    free(readBuffer);
    readBuffer = NULL;
  } while (1);

  if (readBuffer != NULL) {
    free(readBuffer);
  }
}
