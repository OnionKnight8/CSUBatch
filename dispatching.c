/*
#NAME: dispatching.c
#DATE: September 2020
#AUTHORS: Patrick Dooley and Victor Dudley
#DESCRIPTION:
The dispatching module uses the execv() function to run the jobs 
sorted in the job queue and measures the execution time
of each finished job. Based on 'executor' code from Dr. Zhou's
'csubatch_sample.c' amd 'fork_execv.c'.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "dispatching.h"
#include "commandline.h"
#include "jobqueue.h"
#include "main.h"

// Get and set whether is dispatching or not.
int isDispatching;

int getIsDispatching() {
    return isDispatching;
}
void setIsDispatching(int newIsDispatching) {
    isDispatching = newIsDispatching;
}

// Check if program is scheduling
enum check* getSchedulingCheck() 
{
    schedulingCheck = NO;
    return &schedulingCheck;
}

void* dispatching()
{
    pid_t pid;
    //clock_t startTime;
    while(getRunning() == 1 || peek() != NULL)
    {
        //printf("DISPATCHING\n");
        pthread_cond_wait(&cmd_buf_not_empty, &cmd_queue_lock);
        //printf("Unlocked\n");
        /*
        if(schedulingCheck == YES) {
            printf("check success\n");
        }
        else if(schedulingCheck == NO) {
            printf("check fail\n");
        }
        */
        if(schedulingCheck == YES) {
            int runCheck;
            char *my_args[5];

            /*
            my_args[0] = "process";
            my_args[1] = "-help";
            my_args[2] = "setup";
            my_args[3] = NULL;
            */

            my_args[0] = malloc(sizeof(char) * 10);
            sprintf(my_args[0], "%d", peek()->data->executionTime);

            //puts("fork()ing");
            //startTime = clock();
            switch(pid = fork())
            {
                case -1:
                    // Failure
                    perror("Fork Error!");
                    break;
                case 0:
                    // Child
                    execv(peek()->data->name, my_args);
                    puts("Error with execv(). Exiting.");
                    exit(EXIT_FAILURE);
                    break;
                default:
                    // Parent
                    while(waitpid(pid, &runCheck, WNOHANG) == 0); //wait till child process finishes
                    pthread_mutex_lock(&cmd_job_lock);
                    removeJob();
                    //end_t = clock();
                    pthread_mutex_unlock(&cmd_job_lock);
                    //total_t = ((double) (end_t - start_t));
                    break;
            }

            schedulingCheck = NO;
        }
        pthread_cond_signal(&cmd_buf_not_empty);
        pthread_mutex_unlock(&cmd_queue_lock);
    }

    return NULL;
}