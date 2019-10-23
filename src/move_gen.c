#include "defs.h"
#include "board.h"
#include "board_routines.h"

/* ----------------- */

void moveGen_EMPTY(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = EMPTY;
}

/* ----------------- */

void moveGen_wP(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wP;
}

void moveGen_wN(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wN;
}

void moveGen_wB(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wB;
}

void moveGen_wR(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wR;
}

void moveGen_wQ(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wQ;
}

void moveGen_wK(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = wK;
}

/* ----------------- */

void moveGen_bP(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bP;
}

void moveGen_bN(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bN;
}

void moveGen_bB(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bB;
}

void moveGen_bR(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bR;
}

void moveGen_bQ(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bQ;
}

void moveGen_bK(BOARD *cBoard, unsigned char square120)
{
  cBoard->pieces[square120] = bK;
}

/* ----------------- */

void (*MOVE_GEN[13])(BOARD *cBoard, unsigned char square120) = {
  moveGen_EMPTY,

  moveGen_wP,
  moveGen_wN,
  moveGen_wB,
  moveGen_wR,
  moveGen_wQ,
  moveGen_wK,

  moveGen_bP,
  moveGen_bN,
  moveGen_bB,
  moveGen_bR,
  moveGen_bQ,
  moveGen_bK
};

void moveGen(BOARD *cBoard)
{
  unsigned char piece;
  unsigned char square120;
  unsigned char square64;

  for (square64 = 0; square64 < 64; square64 += 1) {
    square120 = board64to120[square64];
    piece = cBoard->pieces[square120];

    (*MOVE_GEN[piece])(cBoard, square120);
  }
}
