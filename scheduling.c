/*
The scheduling module accepts jobs from the user and schedules
them for execution in the dispatching module. It also enforces
the scheduling policy.
*/

#include <stdio.h>


// FCFS (First Come, First Serve)

// This function determines the waiting time.
void getWaitTime(int processes[], int numProcesses, int burstTime[], int waitTime[])
{
    waitTime[0] = 0; // First process

    for(int i = 1; i < numProcesses; i++) {
        waitTime[i] = burstTime[i-1] + waitTime[i-1]; // Burst time is calculated by adding burst time and wait time.
    }
}

// Calculates average time
void getAverageTime(int processes[], int numProcesses, int burstTime[])
{
    int waitTime[numProcesses], turnAroundTime[numProcesses], totalWaitTime = 0, totalTurnAroundTime = 0;\

    getWaitingTime(processes, numProcesses, burstTime, waitTime);
    getTurnAroundTime(processes, numProcesses, burstTime, waitTime, turnAroundTime);


}

// Determines turn around time
void getTurnAroundTime(int processes[], int numProcesses, int burstTime[], int waitTime[], int turnAroundTime[])
{
    for(int i = 0; i < numProcesses; i++) {
        turnAroundTime[i] = burstTime[i] + waitTime[i]; // Turn around time is calculated by adding burst time and wait time.
    }
}


// SJF (Shortest Job First)



// Priority (Priority-Based Scheduling)



int main(int argc, char *argv[])
{

    return 0;
}