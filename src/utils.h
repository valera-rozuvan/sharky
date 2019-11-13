#ifndef __UTILS_H__
#define __UTILS_H__

unsigned char randomR(unsigned char min, unsigned char max);
void sleepMs(int sleepInMs);
int startsWithStr(char *buf, const char *str);
int startsWithStrFF(char **buf, const char *str);
char *stripStr(char *str);

#endif // __UTILS_H__
