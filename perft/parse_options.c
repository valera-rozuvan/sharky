#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned char parseDepthOption(int argc, char *argv[], int idx)
{
  unsigned long long numericParamValue = 0Ul;

  if (idx + 1 >= argc) {
    printf("ERROR: You must provide a positive integer for depth param!\n");
  } else {
    numericParamValue = strtol(argv[idx + 1], NULL, 10);

    if (errno == ERANGE) {
      printf("ERROR: Provided depth is out of range!\n");
      errno = 0;
    } else if ((numericParamValue == 0UL) && (argv[idx + 1][0] != '0')) {
      printf("ERROR: Can't parse depth value!\n");
    } else if ((numericParamValue == 0UL) && (argv[idx + 1][0] == '0')) {
      printf("ERROR: Perft with depth 0 not supported!\n");
    } else if (numericParamValue >= 20) {
      printf("ERROR: Perft with depth >= 20 not supported!\n");
    } else {
      return (unsigned char)numericParamValue;
    }
  }

  return 0;
}

char* parseFENOption(int argc, char *argv[], unsigned char idx)
{
  if (idx + 1 < argc) {
    return argv[idx + 1];
  }

  return NULL;
}
