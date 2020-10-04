/*
#NAME: dispatching.c
#DATE: September 2020
#AUTHORS: Patrick Dooley and Victor Dudley
#DESCRIPTION:
The dispatching module uses the execv() function to run the jobs 
sorted in the job queue and measures the execution time
of each finished job.
*/

#include <stdlib.h>
#include <stdio.h>
#include "dispatching.h"
#include "commandline.h"
#include "jobqueue.h"

// Get and set whether is dispatching or not.
int isDispatching;
int getIsDispatching() {
    return isDispatching;
}
void setIsDispatching(int newIsDispatching) {
    isDispatching = newIsDispatching;
}

void* dispatching()
{
    //u_int i;
    while(getRunning() == 1 || peek() != NULL)
    {
        pthread_cond_wait(&cmd_buf_not_empty, &cmd_queue_lock);
        if(scheduling == 0) {

        }
    }

    return NULL;
}