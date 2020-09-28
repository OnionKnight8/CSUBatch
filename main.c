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
    char userInput[10];
    int valid = 0;

    while(valid = 0)
    {
        fgets(userInput, 10, stdin);
        printf("Hello %s! \n", userInput);

        printf("Taken\n");
        if(strcmp(userInput, commands[0]) == 0) {
            printf("You done it\n");
            valid = 1;
        }
        else {
            printf("Invalid command. Use command 'help' for a list of commands.\n");
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int running = 1;
    int command = -1;

    printf("Welcome to CSUBatch.\n");
    printf("Please enter your command. Use the 'help' command for a list of commands.\n");
    while(running = 1)
    {
        command = getCommand();
    }

    
    return 0;
}