/*
This is the driver for the CSUBatch file. Mostly used to take input
from the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define INPUT_LIMIT 100
#define BUFFER_LENGTH 50

char commands[8][INPUT_LIMIT] = {
    "help", "run", "list", "fcfs", "sjf", "priority", "test", "quit"
};
#

// This is the struct for the buffer used in the producer/consumer design pattern
typedef struct {
    char bufferArray[BUFFER_LENGTH];
    int isOccupied;
    int nextJob;
    int finishedJob;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;

} buffer_t;

buffer_t buffer;

// Takes user input
int getCommand()
{
    char userInput[INPUT_LIMIT];
    int valid = 0;
    int returnCommand = -1;

    while(valid == 0)
    {
        fgets(userInput, INPUT_LIMIT, stdin);
        userInput[strlen(userInput)-1]='\0'; 

        if(strcasecmp(userInput, commands[0]) == 0) {
            valid = 1;
            returnCommand = 1;
        }
        else if(strcasecmp(userInput, commands[1]) == 0) {
            valid = 1;
            returnCommand = 2;
        }
        else if(strcasecmp(userInput, commands[2]) == 0) {
            valid = 1;
            returnCommand = 3;
        }
        else if(strcasecmp(userInput, commands[3]) == 0) {
            valid = 1;
            returnCommand = 4;
        }
        else if(strcasecmp(userInput, commands[4]) == 0) {
            valid = 1;
            returnCommand = 5;
        }
        else if(strcasecmp(userInput, commands[5]) == 0) {
            valid = 1;
            returnCommand = 6;
        }
        else if(strcasecmp(userInput, commands[6]) == 0) {
            valid = 1;
            returnCommand = 7;
        }
        else if(strcasecmp(userInput, commands[7]) == 0) {
            valid = 1;
            returnCommand = 8;
        }
        else {
            printf("Invalid command. Use command 'help' for a list of commands.\n");
        }
    }
    
    fflush(stdin);
    return returnCommand;
}

// Using the producer/consumer design pattern, the scheduling module in the producer.
// This function is for the scheduling thread.
void scheduling (buffer_t *buffer, char job) {
    pthread_mutex_lock(&buffer->mutex);
    
    while(buffer->isOccupied >= BUFFER_LENGTH) {
        pthread_cond_wait(&buffer->less, &buffer->mutex);
    }

    assert(buffer->isOccupied < BUFFER_LENGTH);
    buffer->bufferArray[buffer->nextJob++] = job;
    buffer->nextJob %= BUFFER_LENGTH;
    buffer->isOccupied++;

    pthread_cond_signal(&buffer->more);
    pthread_mutex_unlock(&buffer->mutex);
}

// The consumer is the dispatching module. This fucntion is for the dispatchign thread.
char dispatching (buffer_t *buffer)
{
    char job;
    pthread_mutex_lock(&buffer->mutex);
    while(buffer->isOccupied <= 0) {
        pthread_cond_wait(&buffer->more, &buffer->mutex);

        assert(buffer->isOccupied > 0);
        job = buffer->bufferArray[buffer->nextJob++];
        buffer->nextJob %= BUFFER_LENGTH;
        buffer->isOccupied--;

        pthread_cond_signal(&buffer->less);
        pthread_mutex_unlock(&buffer->mutex);

        return(job);
    }
}

int main(int argc, char *argv[])
{
    int running = 1;
    int command = 0;

    printf("Welcome to CSUBatch.\n");
    
    while(running == 1) {
        printf("Please enter your command. Use the 'help' command for a list of commands.\n");
        command = getCommand();

        switch(command) {
            case 1 :
                printf("HELP\n");
                break;
            case 2 :
                printf("Here is a test run job.\n");
                break;
            case 3 :
                printf("LIST\n");
                break;
            case 4 :
                printf("FCFS\n");
                break;
            case 5 :
                printf("SJF\n");
                break;
            case 6 :
                printf("PRIORITY\n");
                break;
            case 7 :
                printf("TEST\n");
                break;
            case 8 :
                printf("Thank you for using CSUBatch.\n");
                running = 0;
                break;
        }
    }
    
    return 0;
}

