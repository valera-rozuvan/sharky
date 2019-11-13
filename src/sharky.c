#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "human.h"
#include "uci.h"
#include "utils.h"

int main()
{
  char userInput[256] = "";
  char *processedInput;

  srand(time(0));

  printf("%s v%s\n\n%s\n%s %s\n\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_LICENSE, PROGRAM_COPYRIGHT, PROGRAM_AUTHOR);
  printf("Enter 'human' or 'uci': ");

  if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
    exit(EXIT_FAILURE);
  }
  processedInput = stripStr(userInput);

  if (strcmp(processedInput, "human") == 0) {
    free(processedInput);
    human();
  } else if (strcmp(processedInput, "uci") == 0) {
    free(processedInput);
    uci();
  }

  return 0;
}
