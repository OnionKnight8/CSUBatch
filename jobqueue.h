#ifndef JOBQUEUE
#define JOBQUEUE

struct job
{
    char* name;
    int burstTime;
    int priority;
    time_t queueTime;
    int progress;
};

struct node
{
    struct job* data;
    struct node* next;
};

void setSchedulingType(int newSchedulingType);
int getSchedulingType();
struct node* peek();
int enqueue(struct node* newNode);
struct node* dequeue();
void setPointer(struct node* newNode);
int getWaitTime(struct node* newNode);
int newJob(char* jobName, int burstTime, int priority);
void removeJob();
void list();
int getNumJobs();

#endif