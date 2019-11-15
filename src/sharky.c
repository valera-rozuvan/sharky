#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "uci.h"
#include "utils.h"

int main(int argc, char* argv[])
{
  unsigned char idx = 0;

  for (idx = 1; idx < argc; idx += 1) {
    if (strcmp(argv[idx], "--version") == 0) {
      printf("%s v%s\n\n%s\n%s %s\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_LICENSE, PROGRAM_COPYRIGHT, PROGRAM_AUTHOR);

      return 0;
    }
  }

  srand(time(0));
  uci();

  return 0;
}
