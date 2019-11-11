#ifndef __UTILS_H__
#define __UTILS_H__

unsigned char randomR(unsigned char min, unsigned char max);
void sleepMs(int sleepInMs);
char *stripStr(char *text);
int startsWithStr(char *buf, const char *str);
int compareStrFF(char **buf, const char *cmpStr);

#endif // __UTILS_H__
