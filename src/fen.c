#include "board.h"
#include "fen.h"

unsigned char setPositionFromFen(BOARD *cBoard, const char *fenStr)
{
  unsigned char idx = 0;

  for (idx = 0; idx < MAX_ALLOWED_FEN_STRING_LENGTH; idx += 1) {
    if (fenStr[idx] == 0) {
      break;
    }
  }

  if ((idx == 0) || (idx == MAX_ALLOWED_FEN_STRING_LENGTH)) {
    return 1;
  }

  cBoard->fiftyMove = 0;

  return 0;
}
