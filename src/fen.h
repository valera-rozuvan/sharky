#ifndef __FEN_H__
#define __FEN_H__

#include "board.h"

#define MAX_ALLOWED_FEN_STRING_LENGTH 120

unsigned char setPositionFromFen(BOARD *cBoard, const char *fenStr);

#endif // __FEN_H__
