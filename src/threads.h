#ifndef __THREADS_H__
#define __THREADS_H__

#include <pthread.h>

#define THREAD_STATUS_NOT_STARTED 0
#define THREAD_STATUS_STARTING 1
#define THREAD_STATUS_RUNNING 2
#define THREAD_STATUS_STOPPING 3
#define THREAD_STATUS_STOPPED 4
#define THREAD_STATUS_DEAD 5

typedef struct {
  pthread_mutex_t mutex;
  pthread_t thread;
  unsigned int status;
  unsigned int startTime;
} THREAD_PARAMS;

void threadInit(THREAD_PARAMS *threadParams);
void threadDestroy(THREAD_PARAMS *threadParams);
void startThread(void *(*threadFn) (void *), void *threadFnParams, THREAD_PARAMS *threadParams);
void stopThread(THREAD_PARAMS *threadParams);
unsigned int threadAlive(THREAD_PARAMS *threadParams);

#endif // __THREADS_H__
