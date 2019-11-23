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
  unsigned short length = 0, c = 0, d = 0, temp = 0;
  char *start = NULL;

  if (str == NULL) {
    start = (char*)malloc(1);
    if (start == NULL) exit(EXIT_FAILURE);

    *(start) = '\0';
    return start;
  }

  length = strlen(str);

  start = (char*)malloc(length + 1);
  if (start == NULL) exit(EXIT_FAILURE);

  if (length == 0) {
    *(start) = '\0';
    return start;
  }

  c = 0;
  while (*(str + c) != '\0') {
    if (*(str + c) != ' ') {
      break;
    }
    c += 1;
  }

  if (*(str + c) == '\0') {
    *(start) = '\0';
    return start;
  }

  d = 0;
  while (*(str + c) != '\0') {
    if (*(str + c) == ' ') {
      temp = c + 1;
      if (*(str + temp) != '\0') {
        while ((*(str + temp) == ' ') && (*(str + temp) != '\0')) {
          if (*(str + temp) == ' ') {
            c += 1;
          }

          temp += 1;
        }
      }
    }
    *(start + d) = *(str + c);

    c += 1;
    d += 1;
  }

  if ((*(start + d - 1) == '\n') && (*(start + d - 2) == ' ')) {
    *(start + d - 2) = '\0';
  } if ((*(start + d - 1) == '\n') || (*(start + d - 1) == ' ')) {
    *(start + d - 1) = '\0';
  }

  return start;
}
