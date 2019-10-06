#ifndef __VASSERT_H__
#define __VASSERT_H__

#ifndef VASSERT_ENABLE

#define VASSERT_CHAR_EQ(a, b)
#define VASSERT_U_CHAR_EQ(a, b)
#define VASSERT_INT_EQ(a, b)
#define VASSERT_U_INT_EQ(a, b)
#define VASSERT_LONG_LONG_EQ(a, b)
#define VASSERT_U_LONG_LONG_EQ(a, b)

#define VASSERT_TEST()

#else

void vassert_char_eq(char a, char b, char* fileName, int lineNum);
void vassert_u_char_eq(unsigned char a, unsigned char b, char* fileName, int lineNum);
void vassert_int_eq(int a, int b, char* fileName, int lineNum);
void vassert_u_int_eq(unsigned int a, unsigned int b, char* fileName, int lineNum);
void vassert_long_long_eq(long long a, long long b, char* fileName, int lineNum);
void vassert_u_long_long_eq(unsigned long long a, unsigned long long b, char* fileName, int lineNum);

void vassert_test();

#define VASSERT_CHAR_EQ(a, b) vassert_char_eq(a, b, __FILE__, __LINE__);
#define VASSERT_U_CHAR_EQ(a, b) vassert_u_char_eq(a, b, __FILE__, __LINE__);
#define VASSERT_INT_EQ(a, b) vassert_int_eq(a, b, __FILE__, __LINE__);
#define VASSERT_U_INT_EQ(a, b) vassert_u_int_eq(a, b, __FILE__, __LINE__);
#define VASSERT_LONG_LONG_EQ(a, b) vassert_long_long_eq(a, b, __FILE__, __LINE__);
#define VASSERT_U_LONG_LONG_EQ(a, b) vassert_u_long_long_eq(a, b, __FILE__, __LINE__);

#define VASSERT_TEST() vassert_test();

#endif // VASSERT_ENABLE

#endif // __VASSERT_H__

