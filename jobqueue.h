#ifndef JOBQUEUE
#define JOBQUEUE

struct job
{
    char* name;
    int executionTime;
    int priority;
    time_t queueTime;
    int progress;
};

struct node
{
    struct job* data;
    struct node* next;
};

pthread_mutex_t cmd_job_lock; // Lock when job is being scheduled/executed

void create();
int getTotalJobs();
double getTotalTurnTime();
double getTotalExecTime();
double getTotalWaitTime();
double getThroughput();

void setSchedulingType(int newSchedulingType);
int getSchedulingType();
struct node* peek();
int enqueue(struct node* newNode);
struct node* dequeue();
void setPointer(struct node* newNode);
int getWaitTime(struct node* newNode);
int newJob(char* jobName, int executionTime, int priority);
void removeJob();
void list();
int getNumJobs();
void sort(struct node** thisNode);
int changeType(int newType);
void changeOrder();

#endif