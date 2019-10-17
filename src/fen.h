#ifndef __FEN_H__
#define __FEN_H__

#include "board.h"

extern unsigned char MAX_ALLOWED_FEN_STRING_LENGTH;

unsigned char setPositionFromFen(BOARD *cBoard, const char *fenStr);

#endif // __FEN_H__
