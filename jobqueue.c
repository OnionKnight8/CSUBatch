/*
#NAME: jobqueue.c
#DATE: September 2020
#AUTHORS: Patrick Dooley and Victor Dudley
#DESCRIPTION:
The Job Queue module stores jobs for scheduling.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "jobqueue.h"
#include "commandline.h"
#include "main.h"

int numJobs = 0;
int schedulingType = 1;
int totalJobs = 0;
double totalTurnTime = 0;
double totalExecTime = 0;
double totalWaitTime = 0;
double throughput = 0;
char* schedulingTypeString = "FCFS";
struct node* _head = NULL;
struct node* _current = NULL;

int getTotalJobs()
{
    return totalJobs;
}
double getTotalTurnTime()
{
    return totalTurnTime;
}
double getTotalExecTime()
{
    return totalExecTime;
}
double getTotalWaitTime()
{
    return totalWaitTime;
}
double getThroughput()
{
    return throughput;
}

void create()
{
    pthread_mutex_init(&cmd_job_lock, NULL);
    pthread_mutex_lock(&cmd_queue_lock);
}

// Get and set scheduling type
void setSchedulingType(int newSchedulingType) {
    schedulingType = newSchedulingType;
    if(schedulingType == 1) {
        schedulingTypeString = "FCFS";
    }
    else if(schedulingType == 2) {
        schedulingTypeString = "SJF";
    }
    else if(schedulingType == 3) {
        schedulingTypeString = "Priority";
    }
}
int getSchedulingType() {
    return schedulingType;
}

// Return pointer to head of queue
struct node* peek()
{
    return _head;
}

// Allows addition of new nodes into queue
int enqueue(struct node* newNode)
{
    // If queue is empty, insert at head
    if(_head == NULL || _current == NULL) {
        _head = newNode;
        numJobs++;
        totalJobs++;
        return 0;
    }

    int nodeWasSet = 0; // Keep track of weather node was enqued correctly
    if(schedulingType == 1) {
        // FCFS
        _current->next = newNode;
        nodeWasSet = 1;
    }
    else if(schedulingType == 2 && newNode->data->executionTime < _current->data->executionTime) {
        // SJF
        newNode->next = _current;
        _head = newNode;
        nodeWasSet = 1;
    }
    else if(schedulingType == 3 && newNode->data->priority < _current->data->priority) {
        // Priority
        newNode->next = _current;
        _head = newNode;
        nodeWasSet = 1;
    }

    // For determining where next node will be inserted
    if(!nodeWasSet) {
        if(_current->next == NULL) {
            _current->next = newNode;
        }
        else {
            newNode->next = _current->next;
            _current->next = newNode;
        }
    }
    numJobs++;
    totalJobs++;
    return 0;
}

struct node* dequeue()
{
    struct node* old = _head;
    if(_head->next == NULL) {
        _head = NULL;
    }
    else {
        _head = _head->next;
    }
    numJobs--;
    return old;
}

// Sets pointer location
void pointerSet(struct node* newNode)
{
    if(_head == NULL) {
        return;
    }
    _current = _head;
    
    // Move pointer according to scheduling policy.
    if(schedulingType == 1) {
        // FCFS
        while(_current->next != NULL && _current->data->queueTime < newNode->data->queueTime) {
            _current = _current->next;
        }
    }
    else {
        while(_current->next != NULL) {
            _current = _current->next;
        }
    }
}

// Calculates wait time, simply adds all wait times together
int getWaitTime(struct node* newNode)
{
    int waitTime = 0;
    _current = _head;
    while(_current != NULL && _current != newNode) {
        waitTime += _current->data->executionTime;
        _current = _current->next;
    }
    return waitTime;
}

// Allows insertion of new job into queue
int newJob(char* jobName, int jobExecTime, int jobPriority)
{
    // Create new job
    struct job* newJob = (struct job*)(malloc(sizeof(struct job)));
    newJob -> name = jobName;
    newJob -> executionTime = jobExecTime;
    newJob -> priority = jobPriority;
    newJob -> progress = 0;

    // Aquire time added to queue (used for FCFS algorithm)
    time(&(newJob->queueTime));

    // Create node for job
    struct node* newNode = (struct node*)(malloc(sizeof(struct node)));
    newNode -> data = newJob;
    newNode -> next = NULL;
    pointerSet(newNode);
    pthread_mutex_lock(&cmd_job_lock);
    enqueue(newNode);
    pthread_mutex_unlock(&cmd_job_lock);
    if(numJobs == 1) {
        pthread_cond_signal(&cmd_buf_not_empty);
        pthread_mutex_unlock(&cmd_queue_lock);
    }
    int waitTime = 0;
    if(numJobs > 1 && newNode != NULL) {
        waitTime = getWaitTime(newNode);
    }
    
    printf("\nJob %s was submitted.\nTotal number of jobs in the queue: %d\nExpected waiting time: %d\nScheduling Policy: %s\n\n", jobName, numJobs, waitTime, schedulingTypeString);

    return 0;
}

// Remove job and associated node from queue
void removeJob()
{
    //clock_t endTime;
    //endTime = clock();
    //double total_t = ((double) (endTime - startTime));
    //totalExecTime = (totalTurnTime + total_t); // Add turn around time to total turn around time
    //totalWaitTime = ()
    struct node* old = dequeue();
    free(old);
}

// List all jobs in queue.
void list()
{
    printf("Total number of jobs in the queue: %d\n", numJobs);
    printf("Scheduling Policy: %s\n", schedulingTypeString);
    if(_head == NULL) {
        printf("\nThe job queue is currently empty. The 'run' command allows you to add new job.\nType 'help' for more information.\n");
        return;
    }
    printf("Name\tCPU_Time\tPri\tArrival_time\tProgress");
    _current = _head;
    while(_current != NULL){
        struct job* currentJob = _current -> data;
        struct tm* jobTime = localtime(&(currentJob -> queueTime));
        char* jobProgress = " ";
        if(_current->data->progress == 1) {
            jobProgress = "Run";
        }
        printf("\n%s\t%d\t%d\t%d:%d:%d\t\t%s\n", currentJob->name, currentJob->executionTime, currentJob->priority, jobTime->tm_hour, jobTime->tm_min, jobTime->tm_sec, jobProgress);
        _current = _current->next;
    }
}

// Simply return number of jobs
int getNumJobs()
{
    return numJobs;
}

// Selection sort implementation
void sort(struct node** thisNode)
{
    for(int i = 0; i < numJobs; i++) {
        for(int j = i + 1; j < numJobs; j++) {
            if(schedulingType == 1) {
                if(thisNode[i]->data->queueTime > thisNode[j]->data->queueTime && thisNode[i]->data->progress != 1) {
                    struct node* temp = thisNode[i];
                    thisNode[i] = thisNode[j];
                    thisNode[j] = temp;
                }
            }
            else if(schedulingType == 2) {
                if(thisNode[i]->data->executionTime > thisNode[j]->data->executionTime && thisNode[i]->data->progress != 1) {
                    struct node* temp = thisNode[i];
                    thisNode[i] = thisNode[j];
                    thisNode[j] = temp;
                }
            }
            else if(schedulingType == 3) {
                if(thisNode[i]->data->priority > thisNode[j]->data->priority && thisNode[i]->data->progress != 1) {
                    struct node* temp = thisNode[i];
                    thisNode[i] = thisNode[j];
                    thisNode[j] = temp;
                }
            }
        }
    }
}
// Change the scheduling policy
int changeType(int newType)
{
    if(schedulingType == newType)
    {
        printf("Scheduling policy already set to %s. No jobs have been rescheduled.\n", schedulingTypeString);
        return 1;
    }
    setSchedulingType(newType);

    pthread_mutex_lock(&cmd_queue_lock);
    changeOrder();
    pthread_mutex_unlock(&cmd_queue_lock);
    printf("Scheduling policy has been switched to %s. All the %d waiting jobs have been rescheduled.\n", schedulingTypeString, numJobs);
    return 0;
}

// Reorder nodes when type is changed
void changeOrder()
{
    if(numJobs > 1) {
        struct node** thisNode = malloc(sizeof(struct node)*numJobs);
        _current = _head;

        for(int i = 0; i < numJobs; i++) {
            thisNode[i] = _current;
            _current = _current->next;
        }
        sort(thisNode);
        _head = thisNode[0];
        _current = _head;

        for(int i = 1; i < numJobs; i++) {
            _current->next = thisNode[i];
            _current = _current->next;
        }
        _current->next = NULL;
        free(thisNode);
    }
}
