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

int numJobs = 0;
int schedulingType = 1;
char* schedulingTypeString = "FCFS";
struct node* _head = NULL;
struct node* _current = NULL;

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
        return 0;
    }

    int nodeWasSet = 0; // Keep track of weather node was enqued correctly
    if(schedulingType == 1) {
        // FCFS
        _current->next = newNode;
        nodeWasSet = 1;
    }
    else if(schedulingType == 2) {
        // SJF
        nodeWasSet = 1;
    }
    else if(schedulingType == 3) {
        // Priority
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
    else if(schedulingType == 2) {
        // SJF

    }
    else if (schedulingType == 3) {
        // Priority

    }
}

// Calculates wait time, simply adds all wait times together
int getWaitTime(struct node* newNode)
{
    int waitTime = 0;
    _current = _head;
    while(_current != NULL && _current != newNode) {
        waitTime += _current->data->burstTime;
        _current = _current->next;
    }
    return waitTime;
}

// Allows insertion of new job into queue
int newJob(char* jobName, int jobBurstTime, int jobPriority)
{
    // Create new job
    struct job* newJob = (struct job*)(malloc(sizeof(struct job)));
    newJob -> name = jobName;
    newJob -> burstTime = jobBurstTime;
    newJob -> priority = jobPriority;
    newJob -> progress = 0;

    // Aquire time added to queue (used to FCFS algorithm)
    time(&(newJob->queueTime));

    // Create node for job
    struct node* newNode = (struct node*)(malloc(sizeof(struct node)));
    newNode -> data = newJob;
    newNode -> next = NULL;
    pointerSet(newNode);
    enqueue(newNode);

    int waitTime = 0;
    if(numJobs > 1 && newNode != NULL) {
        waitTime = getWaitTime(newNode);
    }
    
    printf("Job %s was submitted.\nTotal number of jobs in the queue: %d\nExpected waiting time: %d\nScheduling Policy:%s\n\n", jobName, numJobs, waitTime, schedulingTypeString);

    return 0;
}

// Remove job and associated node from queue
void removeJob()
{
    struct node* old = dequeue();
    free(old);
}

// List all jobs in queue.
void list()
{
    printf("Total number of jobs in the queue: %d\n", numJobs);
    printf("Scheduling Policy: %s", schedulingTypeString);
    if(_head == NULL) {
        printf("The job queue is currently empty. The 'run' command allows you to add new job.\nType 'help' for more information.\n");
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
        printf("%s\t%d\t%d\t%d:%d:%d\t%s\n", currentJob->name, currentJob->burstTime, currentJob->priority, jobTime->tm_hour, jobTime->tm_min, jobTime->tm_sec, jobProgress);
        _current = _current->next;
    }
}

// Simply return number of jobs
int getNumJobs()
{
    return numJobs;
}