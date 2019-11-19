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
#include "zobrist_hashing.h"
#include "search.h"
#include "threads.h"

#define READ_BUFFER_SIZE 8192

void uciOK()
{
  printf("id name %s %s %s\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_ARCH);
  printf("id author %s\n", PROGRAM_AUTHOR);
  printf("uciok\n");
}

void setupStartPosition(BOARD *cBoard)
{
  setupInitialPosition(cBoard);
  moveGen(cBoard);
  removeIllegalMoves(cBoard);
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

    chessMoveToStr(move, fmtdMove);

    if (startsWithStr(buf, fmtdMove)) return move;
  }

  return 0ULL;
}

void uciSetupStartPosition(BOARD *cBoard, char *buf)
{
  unsigned long long nextMove = 0ULL;

  setupInitialPosition(cBoard);
  moveGen(cBoard);
  removeIllegalMoves(cBoard);

  if (!startsWithStrFF(&buf, "moves")) {
    return;
  }

  do {
    if (*buf == ' ') buf++;

    nextMove = algebraicChessMoveStrToMove(cBoard, buf);
    if (nextMove == 0ULL) break;

    doMove(cBoard, nextMove);
    generateFullHash(cBoard);
    moveGen(cBoard);
    removeIllegalMoves(cBoard);
  } while ((buf = strchr(buf, ' ')));
}

void uci()
{
  BOARD cBoard;
  char *buffer = NULL, *readBuffer = NULL, rawBuffer[READ_BUFFER_SIZE] = "";
  unsigned char isSearching = 0;
  THREAD_PARAMS threadParams;
  SEARCH_THREAD_FN_PARAMS searchThreadFnParams;

  threadInit(&threadParams);

  searchThreadFnParams.cBoard = &cBoard;
  searchThreadFnParams.threadParams = &threadParams;

  setupStartPosition(&cBoard);

  uciOK();

  do {
    if (fgets(rawBuffer, READ_BUFFER_SIZE, stdin) == NULL) {
      sleepMs(2);

      continue;
    }

    readBuffer = stripStr(rawBuffer);
    buffer = readBuffer;

    switch (buffer[0]) {
      case 'i':
        if (strcmp(buffer, "isready") == 0) {
          printf("readyok\n");
        }
        break;

      case 'g':
        if (startsWithStrFF(&buffer, "go")) {
          if (isSearching == 1) {
            stopThread(&threadParams);
          }

          startThread(&search, &searchThreadFnParams, &threadParams);
          isSearching = 1;
        }
        break;

      case 's':
        if (strcmp(buffer, "stop") == 0) {
          if (isSearching == 1) {
            stopThread(&threadParams);
          } else {
            printBestMove(&cBoard);
          }

          isSearching = 0;
        }
        break;

      case 'u':
        if (strcmp(buffer, "ucinewgame") == 0) {
          setupStartPosition(&cBoard);
        } else if (strcmp(buffer, "uci") == 0) {
          uciOK();
        }
        break;

      case 'p':
        if (startsWithStrFF(&buffer, "position")) {
          if (startsWithStrFF(&buffer, "startpos")) {
            uciSetupStartPosition(&cBoard, buffer);
          } else if (startsWithStrFF(&buffer, "fen")) {
            setPositionFromFen(&cBoard, buffer);
            moveGen(&cBoard);
            removeIllegalMoves(&cBoard);
          }
        }
        break;

      case 'q':
        if (strcmp(buffer, "quit") == 0) {
          if (isSearching == 1) {
            stopThread(&threadParams);
          }
          threadDestroy(&threadParams);

          free(readBuffer);
          exit(EXIT_SUCCESS);
        }
        break;
    }

    free(readBuffer);
  } while (1);
}
