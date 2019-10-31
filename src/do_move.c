#include "board.h"
#include "defs.h"

void doMove(BOARD *cBoard, unsigned long long move)
{
  unsigned char fromSq120 = move & 0xFFULL;
  unsigned char toSq120 = (move >> 8) & 0xFFULL;

  unsigned char fromPiece = (move >> 16) & 0xFFULL;
  // unsigned char toPiece = (move >> 20) & 0xFFULL;

  cBoard->pieces[fromSq120] = EMPTY;
  cBoard->pieces[toSq120] = fromPiece;

  if (cBoard->side == WHITE) {
    cBoard->side = BLACK;
  } else {
    cBoard->side = WHITE;
  }
}
