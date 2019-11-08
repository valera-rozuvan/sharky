#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"
#include "human.h"
#include "uci.h"

char *processStr(char *text) {
  int length, c, d;
  char *start;

  c = d = 0;
  length = strlen(text);
  start = (char*)malloc(length + 1);

  if (start == NULL)
    exit(EXIT_FAILURE);

  while (*(text + c) != '\0') {
    if (*(text + c) != ' ') {
      break;
    }
    c++;
  }

  while (*(text + c) != '\0') {
    if (*(text + c) == ' ') {
       int temp = c + 1;
       if (*(text + temp) != '\0') {
          while (*(text + temp) == ' ' && *(text + temp) != '\0') {
             if (*(text + temp) == ' ') {
                c++;
             }
             temp++;
          }
       }
    }
    *(start + d) = *(text + c);
    c++;
    d++;
  }

  if ((*(start + d - 1) == '\n') && (*(start + d - 2) == ' ')) {
    *(start + d - 2) = '\0';
  } if ((*(start + d - 1) == '\n') || (*(start + d - 1) == ' ')) {
    *(start + d - 1) = '\0';
  }

  return start;
}

int main()
{
  char userInput[256] = "";
  char *processedInput;

  printf("%s v%s\n\n%s\n%s %s\n\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_LICENSE, PROGRAM_COPYRIGHT, PROGRAM_AUTHOR);
  printf("Enter 'human' or 'uci': ");

  if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
    exit(EXIT_FAILURE);
  }
  processedInput = processStr(userInput);

  if (strcmp(processedInput, "human") == 0) {
    human();
  } else if (strcmp(processedInput, "uci") == 0) {
    uci();
  }

  free(processedInput);

  return 0;
}
