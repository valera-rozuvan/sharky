#include <pthread.h>

#include "threads.h"
#include "utils.h"

void threadInit(THREAD_PARAMS *threadParams)
{
  threadParams->status = THREAD_STATUS_NOT_STARTED;
  pthread_mutex_init(&threadParams->mutex, NULL);
}

void threadDestroy(THREAD_PARAMS *threadParams)
{
  pthread_mutex_destroy(&threadParams->mutex);
}

void startThread(void *(*threadFn) (void *), void *threadFnParams, THREAD_PARAMS *threadParams)
{
  unsigned char needToStart = 0;

  pthread_mutex_lock(&threadParams->mutex);
  if ((threadParams->status == THREAD_STATUS_NOT_STARTED) || (threadParams->status == THREAD_STATUS_DEAD)) {
    threadParams->status = THREAD_STATUS_STARTING;

    needToStart = 1;
  }
  pthread_mutex_unlock(&threadParams->mutex);

  if (needToStart == 1) {
    pthread_create(&threadParams->thread, NULL, threadFn, threadFnParams);
  }
}

void stopThread(THREAD_PARAMS *threadParams)
{
  unsigned char needToJoin = 0;
  unsigned char threadJoined = 0;

  pthread_mutex_lock(&threadParams->mutex);
  if (threadParams->status == THREAD_STATUS_RUNNING) {
    threadParams->status = THREAD_STATUS_STOPPING;

    needToJoin = 1;
  } else if (threadParams->status == THREAD_STATUS_STOPPED) {
    needToJoin = 1;
  }
  pthread_mutex_unlock(&threadParams->mutex);

  if (needToJoin == 1) {
    do {
      sleepMs(2);

      pthread_mutex_lock(&threadParams->mutex);
      if (threadParams->status == THREAD_STATUS_STOPPED) {
        threadJoined = 1;
        pthread_join(threadParams->thread, NULL);
        threadParams->status = THREAD_STATUS_DEAD;
      }
      pthread_mutex_unlock(&threadParams->mutex);
    } while (threadJoined == 0);
  }
}

unsigned int threadAlive(THREAD_PARAMS *threadParams)
{
  unsigned char returnValue = 0;

  pthread_mutex_lock(&threadParams->mutex);
  if (threadParams->status == THREAD_STATUS_RUNNING) {
    returnValue = 1;
  }
  pthread_mutex_unlock(&threadParams->mutex);

  return returnValue;
}

