#ifndef __UTILS_H__
#define __UTILS_H__

void sleepMs(int sleepInMs);
char *stripStr(char *text);
int startsWithStr(char *buf, const char *str);
int compareStrFF(char **buf, const char *cmpStr);

#endif // __UTILS_H__
