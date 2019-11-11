#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char randomR(unsigned char min, unsigned char max)
{
  double x = (double)rand() / RAND_MAX;
  return (max - min + 1) * x + min;
}

void sleepMs(int sleepInMs)
{
  struct timespec t;
  t.tv_sec = sleepInMs / 1000;
  t.tv_nsec = (sleepInMs % 1000) * 1000000;
  nanosleep(&t, NULL);
}

int startsWithStr(char *buf, const char *str)
{
  return !strncmp(buf, str, strlen(str));
}

/*
 * Compare string, and fast forward to the end of compared block (if match).
 */
int compareStrFF(char **buf, const char *cmpStr)
{
  if (startsWithStr(*buf, cmpStr)) {
    *buf += strlen(cmpStr) + 1;

    return 1;
  }

  return 0;
}

char *stripStr(char *text) {
  int length, c, d;
  char *start;

  c = d = 0;
  length = strlen(text);
  if (length == 0) length = 1;
  start = (char*)malloc(length + 1);

  if (start == NULL)
    exit(EXIT_FAILURE);

  if (length == 1) {
    *(start) = '\0';
    return start;
  }

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