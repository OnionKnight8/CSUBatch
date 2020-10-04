/*
#NAME: scheduling.c
#DATE: September 2020
#AUTHORS: Patrick Dooley and Victor Dudley
#DESCRIPTION:
The scheduling module accepts jobs from the user and schedules
them for execution in the dispatching module. It also enforces
the scheduling policy.
*/

#include <stdio.h>
#include <pthread.h>
#include "main.h"
#include "jobqueue.h"
#include "dispatching.h"

void* scheduling()
{
    // Run while the program is considered "running" and there are jobs to schedule.
    while(getRunning() == 1 || peek() != NULL) {
        pthread_cond_wait(&cmd_buf_not_empty, &cmd_queue_lock); //lock queue
        struct node* head = peek(); // get job from job queue head
        if(head != NULL) {
            if(head->data != NULL) {
                if(head->data->progress == 0) {
                    pthread_mutex_lock(&cmd_job_lock);
                    head->data->progress = 1; // job is considered running
                    pthread_mutex_unlock(&cmd_job_lock);
                }
            }
        }
        pthread_mutex_unlock(&cmd_queue_lock); // unlock queue
    }
    return NULL;
}