#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "board.h"
#include "threads.h"

typedef struct {
  BOARD *cBoard;
  THREAD_PARAMS *threadParams;
} SEARCH_THREAD_FN_PARAMS;

void *search(void *threadFnParams);

#endif // __SEARCH_H__
