#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "defs_arch.h"
#include "uci.h"

int main(int argc, char* argv[])
{
  unsigned char idx = 0;

  for (idx = 1; idx < argc; idx += 1) {
    if (strcmp(argv[idx], "--version") == 0) {
      printf("%s v%s %s\n\n%s\n%s %s\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_ARCH, PROGRAM_LICENSE, PROGRAM_COPYRIGHT, PROGRAM_AUTHOR);

      exit(EXIT_SUCCESS);
      return 0;
    }
  }

  srand(time(0));
  uci();

  // uci() function will call exit(EXIT_SUCCESS) when GUI sends a `quit` command.
  // Therefore, we should never reach this place in code.
  // If we reached this place - let's notify the system that the program did something wrong.

  exit(EXIT_FAILURE);
  return 1;
}
