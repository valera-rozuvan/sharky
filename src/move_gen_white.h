#ifndef __MOVE_GEN_WHITE_H__
#define __MOVE_GEN_WHITE_H__

#include "board.h"

void moveGen_wP_normal_advance(BOARD *cBoard, unsigned char square120);
void moveGen_wP_promote_advance(BOARD *cBoard, unsigned char square120);
void moveGen_wP_double_advance(BOARD *cBoard, unsigned char square120);
void moveGen_wP_normal_capture(BOARD *cBoard, unsigned char square120);
void moveGen_wP_promote_capture(BOARD *cBoard, unsigned char square120);
void moveGen_wP_en_passant_capture(BOARD *cBoard, unsigned char square120);
void moveGen_wP(BOARD *cBoard, unsigned char square120);
void moveGen_wN(BOARD *cBoard, unsigned char square120);
void moveGen_white_sliding_piece(
  BOARD *cBoard, unsigned char square120,
  unsigned char piece, unsigned char (*moveDisplacements)[], unsigned char moveDisplacementsCount
);
void moveGen_wB(BOARD *cBoard, unsigned char square120);
void moveGen_wR(BOARD *cBoard, unsigned char square120);
void moveGen_wQ(BOARD *cBoard, unsigned char square120);
void moveGen_wK(BOARD *cBoard, unsigned char square120);

#endif // __MOVE_GEN_WHITE_H__
