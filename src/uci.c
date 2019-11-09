#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "defs_arch.h"
#include "utils.h"

#define READ_BUFFER_SIZE 8192

void uci()
{
  char *buffer = NULL, *readBuffer = NULL, rawBuffer[READ_BUFFER_SIZE] = "";

  printf("%s %s %s by %s\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_ARCH, PROGRAM_AUTHOR);

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
    } else if (compareStrFF(&buffer, "quit")) {
      break;
    }

    free(readBuffer);
    readBuffer = NULL;
  } while (1);

  if (readBuffer != NULL) {
    free(readBuffer);
  }
}
