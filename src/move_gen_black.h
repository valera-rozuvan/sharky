#ifndef __MOVE_GEN_BLACK_H__
#define __MOVE_GEN_BLACK_H__

#include "board.h"

void moveGen_bP_normal_advance(BOARD *cBoard, unsigned char square120);
void moveGen_bP_promote_advance(BOARD *cBoard, unsigned char square120);
void moveGen_bP_double_advance(BOARD *cBoard, unsigned char square120);
void moveGen_bP_normal_capture(BOARD *cBoard, unsigned char square120);
void moveGen_bP_promote_capture(BOARD *cBoard, unsigned char square120);
void moveGen_bP_en_passant_capture(BOARD *cBoard, unsigned char square120);
void moveGen_bP(BOARD *cBoard, unsigned char square120);
void moveGen_bN(BOARD *cBoard, unsigned char square120);
void moveGen_black_sliding_piece(
  BOARD *cBoard, unsigned char square120,
  unsigned char piece, unsigned char (*moveDisplacements)[], unsigned char moveDisplacementsCount
);
void moveGen_bB(BOARD *cBoard, unsigned char square120);
void moveGen_bR(BOARD *cBoard, unsigned char square120);
void moveGen_bQ(BOARD *cBoard, unsigned char square120);
void moveGen_bK(BOARD *cBoard, unsigned char square120);

#endif // __MOVE_GEN_BLACK_H__
