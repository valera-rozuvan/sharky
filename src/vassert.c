#ifdef VASSERT_ENABLE

#include "stdio.h"
#include "stdlib.h"

#include "vassert.h"

void commonInfo(char* fileName, int lineNum)
{
  printf("On %s\n", __DATE__);
  printf("At %s\n", __TIME__);
  printf("In file %s\n", fileName);
  printf("At line %d\n", lineNum);

  printf("\nExiting...\n");
  exit(1);
}

void vassert_char_eq(char a, char b, char* fileName, int lineNum)
{
  if (a != b) {
    printf("Assert failed! %hhi != %hhi \n", a, b);

    commonInfo(fileName, lineNum);
  }
}

void vassert_u_char_eq(unsigned char a, unsigned char b, char* fileName, int lineNum)
{
  if (a != b) {
    printf("Assert failed! %hhu != %hhu \n", a, b);

    commonInfo(fileName, lineNum);
  }
}

void vassert_int_eq(int a, int b, char* fileName, int lineNum)
{
  if (a != b) {
    printf("Assert failed! %d != %d \n", a, b);

    commonInfo(fileName, lineNum);
  }
}

void vassert_u_int_eq(unsigned int a, unsigned int b, char* fileName, int lineNum)
{
  if (a != b) {
    printf("Assert failed! %u != %u \n", a, b);

    commonInfo(fileName, lineNum);
  }
}

void vassert_long_long_eq(long long a, long long b, char* fileName, int lineNum)
{
  if (a != b) {
    printf("Assert failed! %lli != %lli \n", a, b);

    commonInfo(fileName, lineNum);
  }
}

void vassert_u_long_long_eq(unsigned long long a, unsigned long long b, char* fileName, int lineNum)
{
  if (a != b) {
    printf("Assert failed! %llu != %llu \n", a, b);

    commonInfo(fileName, lineNum);
  }
}

void vassert_test()
{
  char largeChar = 127;
  unsigned char largeUChar = 255;
  int largeInt = 32767;
  unsigned int largeUInt = 65535;
  long long largeLongLong = 9223372036854775807;
  unsigned long long largeULongLong = 18446744073709551615ULL;

  VASSERT_CHAR_EQ(largeChar, 127);
  VASSERT_U_CHAR_EQ(largeUChar, 255);
  VASSERT_INT_EQ(largeInt, 32767);
  VASSERT_U_INT_EQ(largeUInt, 65535);
  VASSERT_LONG_LONG_EQ(largeLongLong, 9223372036854775807);
  VASSERT_U_LONG_LONG_EQ(largeULongLong, 18446744073709551615ULL);
}

#endif // VASSERT_ENABLE
