#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "defs_arch.h"
#include "utils.h"
#include "board_routines.h"
#include "fen.h"
#include "move_gen.h"
#include "bitboard.h"
#include "do_move.h"
#include "utils.h"
#include "zobrist_hashing.h"

#define READ_BUFFER_SIZE 8192

void uciOK()
{
  printf("id name %s %s %s\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_ARCH);
  printf("id author %s\n", PROGRAM_AUTHOR);
  printf("uciok\n");
}

unsigned long long algebraicChessMoveStrToMove(BOARD *cBoard, char *buf)
{
  unsigned char idx = 0;
  char fmtdMove[MAX_MOVE_STR_LENGTH] = "";
  unsigned long long move = 0ULL;

  if (cBoard->movesAvailable == 0) return 0ULL;

  for (idx = 0; idx < cBoard->movesAvailable; idx += 1) {
    move = cBoard->moves[idx];

    if (CHECK_BIT(move, MOVE_BIT_ILLEGAL)) continue;

    chessMoveToAlgebraicStr(move, fmtdMove);

    if (startsWithStr(buf, fmtdMove)) return move;
  }

  return 0ULL;
}

void uciSetupStartPosition(BOARD *cBoard, char *buf)
{
  char nextMove[MAX_MOVE_STR_LENGTH] = "";
  unsigned char idx = 0;

  setupInitialPosition(cBoard);
  moveGen(cBoard);
  removeIllegalMoves(cBoard);

  if (!compareStrFF(&buf, "moves")) {
    return;
  }

  for (idx = 0; idx < MAX_MOVE_STR_LENGTH; idx += 1) {
    if ((buf[idx] == ' ') || (buf[idx] == '\n') || (buf[idx] == '\0')) {
      nextMove[idx] = '\0';

      break;
    } else {
      nextMove[idx] = buf[idx];
    }
  }

  doMove(cBoard, algebraicChessMoveStrToMove(cBoard, nextMove));
  generateFullHash(cBoard);
  moveGen(cBoard);
  removeIllegalMoves(cBoard);

  while ((buf = strchr(buf, ' ')))
  {
    while (*buf == ' ') buf++;

    for (idx = 0; idx < MAX_MOVE_STR_LENGTH; idx += 1) {
      if ((buf[idx] == ' ') || (buf[idx] == '\n') || (buf[idx] == '\0')) {
        nextMove[idx] = '\0';

        break;
      } else {
        nextMove[idx] = buf[idx];
      }
    }

    doMove(cBoard, algebraicChessMoveStrToMove(cBoard, buf));
    generateFullHash(cBoard);
    moveGen(cBoard);
    removeIllegalMoves(cBoard);
  }
}

void printBestMove(BOARD *cBoard)
{
  char fmtdMove[MAX_MOVE_STR_LENGTH] = "";
  unsigned char idx1 = 0, idx2 = 0;

  if (cBoard->movesAvailable == 0) {
    printf("bestmove 0000\n");
    return;
  } else if (cBoard->movesAvailable == 1) {
    if (CHECK_BIT(cBoard->moves[0], MOVE_BIT_ILLEGAL)) {
      printf("bestmove 0000\n");
      return;
    } else {
      chessMoveToAlgebraicStr(cBoard->moves[0], fmtdMove);
      printf("bestmove %s\n", fmtdMove);
      return;
    }
  } else {
    do {
      if (idx2 >= cBoard->movesAvailable * 30) break;

      idx1 = randomR(0, cBoard->movesAvailable - 1);
      idx2 += 1;
    } while (CHECK_BIT(cBoard->moves[idx1], MOVE_BIT_ILLEGAL));

    if (idx2 >= cBoard->movesAvailable * 30) {
      printf("bestmove 0000\n");
    } else {
      chessMoveToAlgebraicStr(cBoard->moves[idx1], fmtdMove);
      printf("bestmove %s\n", fmtdMove);
    }
  }
}

void uci()
{
  BOARD cBoard;
  char *buffer = NULL, *readBuffer = NULL, rawBuffer[READ_BUFFER_SIZE] = "";

  setupInitialPosition(&cBoard);
  moveGen(&cBoard);
  removeIllegalMoves(&cBoard);

  uciOK();

  setbuf(stdout, NULL);

  do {
    if (fgets(rawBuffer, READ_BUFFER_SIZE, stdin) == NULL) {
      sleepMs(2);

      continue;
    }

    readBuffer = stripStr(rawBuffer);
    buffer = readBuffer;

    if (compareStrFF(&buffer, "isready")) {
      printf("readyok\n");
    } else if (compareStrFF(&buffer, "stop")) {
      // Always send the best move when engine stops searching.

      // TODO: Actually send the best move ;)
      printBestMove(&cBoard);
    } else if (compareStrFF(&buffer, "quit")) {
      break;
    } else if (compareStrFF(&buffer, "ucinewgame")) {
      setupInitialPosition(&cBoard);
      moveGen(&cBoard);
      removeIllegalMoves(&cBoard);
    } else if (compareStrFF(&buffer, "position fen")) {
      setPositionFromFen(&cBoard, buffer);
      moveGen(&cBoard);
      removeIllegalMoves(&cBoard);
    } else if (compareStrFF(&buffer, "position startpos")) {
      uciSetupStartPosition(&cBoard, buffer);
    } else if (compareStrFF(&buffer, "print moves")) {
      printMoves(&cBoard);
    } else if (compareStrFF(&buffer, "print")) {
      printBoard(&cBoard);
    } else if (compareStrFF(&buffer, "uci")) {
      uciOK();
    } else if (compareStrFF(&buffer, "go")) {
      printBestMove(&cBoard);
    }

    free(readBuffer);
    readBuffer = NULL;
  } while (1);

  if (readBuffer != NULL) {
    free(readBuffer);
  }
}
