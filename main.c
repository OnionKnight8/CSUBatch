/*
#NAME: main.c
#DATE: September 2020
#AUTHORS: Patrick Dooley and Victor Dudley
#DESCRIPTION:
This is the driver for the CSUBatch file. Based on Dr. Zhou's 'csubatch_sample.c' and 
'The Producer/Consumer Problem' from docs.oracle.com.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include "main.h"
#include "commandline.h"
#include "scheduling.h"
#include "dispatching.h"

int isRunning = 1;

int main(int argc, char *argv[])
{
    //clock_program_start();

    pthread_t scheduling_thread, dispatching_thread;

    // Create threads
    pthread_create(&scheduling_thread, NULL, &scheduling, NULL);
    pthread_create(&dispatching_thread, NULL, &dispatching, NULL);

    // Initialize lock and condition variables
    pthread_mutex_init(&cmd_queue_lock, NULL);
    pthread_mutex_init(&cmd_job_lock, NULL);
    pthread_cond_init(&cmd_buf_not_full, NULL);
    pthread_cond_init(&cmd_buf_not_empty, NULL);

    // Main will not continue until threads are complete.
    //pthread_join(scheduling_thread, NULL);
    //pthread_join(dispatching_thread, NULL);

    commandLineLoop();

    pthread_mutex_destroy(&cmd_queue_lock);
    pthread_cond_destroy(&cmd_buf_not_full);
    pthread_cond_destroy(&cmd_buf_not_empty);
    return 0;
}

// Getter and setter to determine if program is running
int getRunning()
{
    return isRunning;
}
void setRunning(int newIsRunning)
{
    isRunning = newIsRunning;
}
