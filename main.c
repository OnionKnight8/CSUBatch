/*
This is the driver for the CSUBatch file. Mostly used to take input
from the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char commands[8][100] = {
    "help", "run", "list", "fcfs", "sjf", "priority", "test", "quit"
};

// Takes user input
int getCommand()
{
    char userInput[100];
    int valid = 0;
    int returnCommand = -1;

    while(valid == 0)
    {
        fgets(userInput, 100, stdin);
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
                printf("RUN\n");
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

