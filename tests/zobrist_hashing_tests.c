#include <stdlib.h>
#include <stdio.h>

#include "../src/board.h"
#include "../src/board_routines.h"
#include "../src/random_const.h"
#include "../src/zobrist_hashing.h"
#include "../src/bitboard.h"

#include "zobrist_hashing_tests.h"
#include "tests.h"

unsigned long long INITIAL_POSITION_ZOBRIST_KEY = 0xef03a45ed3c2355fULL;

void testEmptyPosition()
{
  BOARD cBoard;

  setupEmptyPosition(&cBoard);

  if (cBoard.positionKey != 0x0ULL) {
    fprintf(stderr, "ERROR: Empty position hash key is wrong! cBoard.positionKey = %llx\n", cBoard.positionKey);
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }
}

void testStartPosition()
{
  BOARD cBoard;

  setupInitialPosition(&cBoard);

  if (cBoard.positionKey != INITIAL_POSITION_ZOBRIST_KEY) {
    fprintf(stderr, "ERROR: Initial position hash key is wrong! cBoard.positionKey = %llx\n", cBoard.positionKey);
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }
}

/*
 *   wP = 1, wN = 2, wB = 3, wR = 4,  wQ = 5,  wK = 6,
 *   bP = 7, bN = 8, bB = 9, bR = 10, bQ = 11, bK = 12
 */

const unsigned char pieceList[12] = {
  wP, wN, wB, wR, wQ, wK,
  bP, bN, bB, bR, bQ, bK
};

void testIndividualPieces()
{
  unsigned short idx1 = 0;
  unsigned short idx2 = 0;
  unsigned char sq120 = 0;
  unsigned short hashCounter = 0;

  unsigned long long hashArr[RANDOM_CONST_LENGTH];
  unsigned char hashArr_piece[RANDOM_CONST_LENGTH];
  unsigned char hashArr_sqr64[RANDOM_CONST_LENGTH];

  BOARD cBoard;

  setupEmptyPosition(&cBoard);

  for (idx1 = 0; idx1 < 12; idx1 += 1) {
    if ((pieceList[idx1] == wP) || (pieceList[idx1] == bP)) {
      for (idx2 = 8; idx2 <= 55; idx2 += 1) {
        sq120 = board64to120[idx2];

        cBoard.pieces[sq120] = pieceList[idx1];
        hashArr[hashCounter] = generateFullHash(&cBoard);
        hashArr_piece[hashCounter] = pieceList[idx1];
        hashArr_sqr64[hashCounter] = idx2;
        hashCounter += 1;
        cBoard.pieces[sq120] = EMPTY;
      }
    } else {
      for (idx2 = 0; idx2 <= 63; idx2 += 1) {
        sq120 = board64to120[idx2];

        cBoard.pieces[sq120] = pieceList[idx1];
        hashArr[hashCounter] = generateFullHash(&cBoard);
        hashArr_piece[hashCounter] = pieceList[idx1];
        hashArr_sqr64[hashCounter] = idx2;
        hashCounter += 1;
        cBoard.pieces[sq120] = EMPTY;
      }
    }
  }

  cBoard.side = BLACK;
  hashArr[hashCounter] = generateFullHash(&cBoard);
  hashCounter += 1;
  cBoard.side = WHITE;

  SET_BIT(cBoard.castlingPerm, WKCastling);
  hashArr[hashCounter] = generateFullHash(&cBoard);
  hashCounter += 1;
  CLEAR_BIT(cBoard.castlingPerm, WKCastling);

  SET_BIT(cBoard.castlingPerm, WQCastling);
  hashArr[hashCounter] = generateFullHash(&cBoard);
  hashCounter += 1;
  CLEAR_BIT(cBoard.castlingPerm, WQCastling);

  SET_BIT(cBoard.castlingPerm, BKCastling);
  hashArr[hashCounter] = generateFullHash(&cBoard);
  hashCounter += 1;
  CLEAR_BIT(cBoard.castlingPerm, BKCastling);

  SET_BIT(cBoard.castlingPerm, BQCastling);
  hashArr[hashCounter] = generateFullHash(&cBoard);
  hashCounter += 1;
  CLEAR_BIT(cBoard.castlingPerm, BQCastling);

  for (idx1 = FILE_A; idx1 <= FILE_H; idx1 += 1) {
    cBoard.enPassantFile = idx1;
    hashArr[hashCounter] = generateFullHash(&cBoard);
    hashCounter += 1;
    cBoard.enPassantFile = NO_EN_PASSANT;
  }

  if (hashCounter != RANDOM_CONST_LENGTH) {
    fprintf(stderr, "ERROR: Error! Not all random constants were used! hashCounter = %hu, RANDOM_CONST_LENGTH = %hu\n", hashCounter, RANDOM_CONST_LENGTH);
    exit(EXIT_FAILURE);
  } else {
    totalChecksPerformed += 1;
  }

  for (idx1 = 0; idx1 < RANDOM_CONST_LENGTH; idx1 += 1) {
    for (idx2 = idx1 + 1; idx2 < RANDOM_CONST_LENGTH; idx2 += 1) {
      if (hashArr[idx1] == hashArr[idx2]) {
        fprintf(stderr, "ERROR: Position hash collision detected!\n");
        fprintf(stderr, "ERROR: idx1 = %hu, idx2 = %hu\n", idx1, idx2);
        fprintf(stderr, "ERROR: hashArr[idx1] = %llx, hashArr[idx2] = %llx\n", hashArr[idx1], hashArr[idx2]);

        if (idx1 <= 735) {
          fprintf(stderr, "ERROR: hashArr_piece[idx1] = %hhu\n", hashArr_piece[idx1]);
          fprintf(stderr, "ERROR: hashArr_sqr64[idx1] = %hhu\n", hashArr_sqr64[idx1]);
        }

        if (idx2 <= 735) {
          fprintf(stderr, "ERROR: hashArr_piece[idx2] = %hhu\n", hashArr_piece[idx2]);
          fprintf(stderr, "ERROR: hashArr_sqr64[idx2] = %hhu\n", hashArr_sqr64[idx2]);
        }

        exit(EXIT_FAILURE);
      } else {
        totalChecksPerformed += 1;
      }
    }
  }
}

void zobrist_hashing_tests()
{
  printf("Starting zobrist_hashing_tests...\n");

  testEmptyPosition();
  testStartPosition();
  testIndividualPieces();

  printf("Done!\n\n");
}
