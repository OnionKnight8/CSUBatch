/*
This is the driver for the CSUBatch file.
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

        if(strcmp(userInput, commands[0]) == 0) {
            printf("HELP\n");
            valid = 1;
            returnCommand = 1;
        }
        else if(strcmp(userInput, commands[1]) == 0) {
            printf("RUN\n");
            valid = 1;
            returnCommand = 2;
        }
        else if(strcmp(userInput, commands[2]) == 0) {
            printf("LIST\n");
            valid = 1;
            returnCommand = 3;
        }
        else if(strcmp(userInput, commands[3]) == 0) {
            printf("FCFS\n");
            valid = 1;
            returnCommand = 4;
        }
        else if(strcmp(userInput, commands[4]) == 0) {
            printf("SJF\n");
            valid = 1;
            returnCommand = 5;
        }
        else if(strcmp(userInput, commands[5]) == 0) {
            printf("PRIORITY\n");
            valid = 1;
            returnCommand = 6;
        }
        else if(strcmp(userInput, commands[6]) == 0) {
            printf("TEST\n");
            valid = 1;
            returnCommand = 7;
        }
        else if(strcmp(userInput, commands[7]) == 0) {
            valid = 1;
            returnCommand = 8;
        }
        else {
            printf("Invalid command. Use command 'help' for a list of commands.\n");
        }
    }
    
    return returnCommand;
}

int main(int argc, char *argv[])
{
    int running = 1;
    int command = 0;

    printf("Welcome to CSUBatch.\n");
    printf("Please enter your command. Use the 'help' command for a list of commands.\n");
    
    while(running == 1) {
        command = getCommand();

        if(command == 1){
            //help
        }
        else if(command == 2) {
            //run
        }
        else if(command == 3) {
            //list
        }
        else if(command == 4) {
            //fcfs
        }
        else if(command == 5) {
            //sjf
        }
        else if(command == 6) {
            //priority
        }
        else if(command == 7) {
            //test
        }
        else{
            printf("Thank you for using CSUBatch.\n");
            running = 0;
            break;
        }
        printf("Please enter your next command. Use 'help' to list all commands.\n");
    }
    
    return 0;
}

