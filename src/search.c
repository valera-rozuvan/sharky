#include "search.h"
#include "board.h"
#include "threads.h"
#include "utils.h"
#include "board_routines.h"
#include "bitboard.h"

void bestMoveIsRndMove(BOARD *cBoard)
{
  unsigned char idx = 0;
  unsigned long long passiveMoves[MAX_POSSIBLE_MOVES_IN_POSITION];
  unsigned char passiveMovesLength = 0;
  unsigned long long captureMoves[MAX_POSSIBLE_MOVES_IN_POSITION];
  unsigned char captureMovesLength = 0;
  unsigned long long move = 0ULL;

  if (cBoard->movesAvailable == 0) {
    cBoard->bestMove = 0ULL;
    return;
  }

  if (cBoard->movesAvailable == 1) {
    if (CHECK_BIT(cBoard->moves[0], MOVE_BIT_ILLEGAL)) {
      cBoard->bestMove = 0ULL;
      return;
    }

    cBoard->bestMove = cBoard->moves[0];
    return;
  }

  for (idx = 0; idx < cBoard->movesAvailable; idx += 1) {
    move = cBoard->moves[idx];

    if (CHECK_BIT(move, MOVE_BIT_ILLEGAL)) continue;

    if (CHECK_BIT(move, MOVE_BIT_CAPTURE)) {
      captureMoves[captureMovesLength] = move;
      captureMovesLength += 1;

      continue;
    }

    if (captureMovesLength > 0) continue;

    passiveMoves[passiveMovesLength] = move;
    passiveMovesLength += 1;
  }

  if ((captureMovesLength == 0) && (passiveMovesLength == 0)) {
    cBoard->bestMove = 0ULL;
    return;
  }

  if (captureMovesLength > 0) {
    idx = randomR(0, captureMovesLength - 1);
    cBoard->bestMove = captureMoves[idx];
  } else {
    idx = randomR(0, passiveMovesLength - 1);
    cBoard->bestMove = passiveMoves[idx];
  }
}

void *search(void *threadFnParams)
{
  SEARCH_THREAD_FN_PARAMS *searchThreadFnParams = (SEARCH_THREAD_FN_PARAMS*)threadFnParams;
  BOARD *cBoard = searchThreadFnParams->cBoard;
  THREAD_PARAMS *threadParams = searchThreadFnParams->threadParams;

  pthread_mutex_lock(&threadParams->mutex);
  threadParams->status = THREAD_STATUS_RUNNING;
  pthread_mutex_unlock(&threadParams->mutex);

  do {
    bestMoveIsRndMove(cBoard);

    sleepMs(2);

    // TODO: Actually break out of the loop based on time control settings.
    break;
  } while (threadAlive(threadParams) == 1);

  printBestMove(cBoard);

  return NULL;
}
