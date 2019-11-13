#include <pthread.h>

#include "threads.h"

void startThread(void *(*threadFn) (void *), void *threadFnParams, THREAD_PARAMS *threadParams)
{
  unsigned char needToStart = 0;

  pthread_mutex_lock(&threadParams->mutex);
  if ((threadParams->status == THREAD_STATUS_NOT_STARTED) || (threadParams->status == THREAD_STATUS_STOPPED)) {
    threadParams->status = THREAD_STATUS_NOT_STARTING;

    needToStart = 1;
  }
  pthread_mutex_unlock(&threadParams->mutex);

  if (needToStart == 1) {
    pthread_create(&threadParams->thread, NULL, threadFn, threadFnParams);
  }
}

void stopThread(THREAD_PARAMS *threadParams)
{
  unsigned char needToStop = 0;

  pthread_mutex_lock(&threadParams->mutex);
  if (threadParams->status == THREAD_STATUS_RUNNING) {
    threadParams->status = THREAD_STATUS_STOPPING;

    needToStop = 1;
  }
  pthread_mutex_unlock(&threadParams->mutex);

  if (needToStop == 1) {
    pthread_join(threadParams->thread, NULL);

    pthread_mutex_lock(&threadParams->mutex);
    threadParams->status = THREAD_STATUS_STOPPED;
    pthread_mutex_unlock(&threadParams->mutex);
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

