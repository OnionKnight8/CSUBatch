// Header file for main.c

#ifndef MAIN
#define MAIN

#include <pthread.h>

//#define INPUT_LIMIT 500 // Character limit for inputs
//#define BUFFER_LENGTH 10 // Command queue length
//#define COMMAND_AMOUNT 5 // Number of submitted jobs
//#define LOW_SERVICE_RATE // Long service time

typedef unsigned int u_int;

pthread_mutex_t cmd_queue_lock; // Critical section lock
//pthread_mutex_t cmd_job_lock; // Lock when job is being scheduled/executed
//pthread_cond_t cmd_buf_not_full; // Condition variable for buf_not_full
pthread_cond_t cmd_buf_not_empty; // Condition variable for buf_not_empty
pthread_t scheduling_thread;
pthread_t dispatching_thread;
//char *cmd_buffer[BUFFER_LENGTH];
//u_int head;
//u_int tail;
//u_int count;
int getRunning();
void setRunning(int newIsRunning);

// pthreads only accept void* conditions so we need to enumerate conditions
enum check
{
    YES = 0,
    NO = 1
};

#endif