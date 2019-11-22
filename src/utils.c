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

/*
 * Does the `buf` start with `str`?
 */
int startsWithStr(char *buf, const char *str)
{
  if (buf == NULL) return 0;
  if (str == NULL) return 0;
  if (str[0] == '\0') return 0;

  return !strncmp(buf, str, strlen(str));
}

/*
 * Does the `buf` start with `str`?
 * Fast forward `buf` to the end of compared `str` (if match).
 */
int startsWithStrFF(char **buf, const char *str)
{
  if (startsWithStr(*buf, str)) {
    *buf += strlen(str) + 1;

    return 1;
  }

  return 0;
}

char *stripStr(char *str) {
  int length, c, d;
  char *start;

  c = d = 0;
  length = strlen(str);
  if (length == 0) length = 1;
  start = (char*)malloc(length + 1);

  if (start == NULL)
    exit(EXIT_FAILURE);

  if (length == 1) {
    *(start) = '\0';
    return start;
  }

  while (*(str + c) != '\0') {
    if (*(str + c) != ' ') {
      break;
    }
    c++;
  }

  while (*(str + c) != '\0') {
    if (*(str + c) == ' ') {
       int temp = c + 1;
       if (*(str + temp) != '\0') {
          while (*(str + temp) == ' ' && *(str + temp) != '\0') {
             if (*(str + temp) == ' ') {
                c++;
             }
             temp++;
          }
       }
    }
    *(start + d) = *(str + c);
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
