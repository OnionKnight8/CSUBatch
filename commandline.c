/*
#NAME: commandline.c
#DATE: September 2020
#AUTHORS: Patrick Dooley and Victor Dudley
#DESCRIPTION:
Input parser for the CSUBatch application. Based on Dr. Zhou's 'commandline_parser.c'.
*/

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "commandline.h"

// Error codes
#define EINVAL  1
#define E2BIG   2
#define MAXMENUARGS 4
#define MAXCMDLINE  64

// Run
int cmd_run(int nargs, char **args)
{
    if(nargs != 4) {
        printf("Invalid command. Enter 'run <job> <time> <priority>\n");
    }

    //todo: execv command to dispatch
    return 0;
}

// Quit
int cmd_quit(int nargs, char **args)
{
    //todo: add performance stats
    exit(0);
}

// Menu
void showmenu(const char *x[])
{
    /*
    int ct, half, i;
    printf("\n");

    for(i = ct = 0; x[i]; i++) {
        ct++;
    }
    half = (ct + 1) / 2;

    for(i = 0; i<half; i++) {
        printf("    %-36s", x[i]);
        if(i + half < ct) {
            printf("%s", x[i + half]);
        }
        printf("\n");
    }
    */
    for(int i = 0; x[i]; i++) {
        printf("%s\n", x[i]);
    }
    printf("\n");
}

// Help table
static const char *helpmenu[] =
{
    "run <job <time> <pri>: Submit a job named <job>,\n\t\t\texecution time is <time>\n\t\t\tpriority is <pri>.",
    "list: display the job status.",
    "fcfs: change the scheduling policy to FCFS.",
    "sjf: change the scheduling policy to SJF.",
    "priority: change the scheduling policy to priority.",
    "test <benchmark> <policy> <num_of_jobs> <priority_levels>\n\t<min_CPU_time> <max_CPU_time>",
    "quit: exit CSUBatch",
    NULL
};

int cmd_helpmenu(int n, char **a)
{
    (void)n;
    (void)a;

    showmenu(helpmenu);
    return 0;
}

// Command table
static struct {
    const char *name;
    int(*func)(int nargs, char **args);
} cmdtable[] = {
    { "?\n",	cmd_helpmenu },
	{ "h\n",	cmd_helpmenu },
	{ "help\n",	cmd_helpmenu },
    { "run\n", cmd_run },
    //{ "list\n", cmd_list },
    //{ "fcfs\n", cmd_fcfs },
    //{ "sjf\n", cmd_sjf },
    //{ "priority\n", cmd_priority },
    //{ "test\n", cmd_test },
	{ "q\n",	cmd_quit },
	{ "quit\n",	cmd_quit },
    {NULL, NULL}
};

// Process a single command
int cmd_dispatch(char *cmd)
{
	time_t beforesecs, aftersecs, secs;
	u_int32_t beforensecs, afternsecs, nsecs;
	char *args[MAXMENUARGS];
	int nargs=0;
	char *word;
	char *context;
 	int i, result;

	for (word = strtok_r(cmd, " ", &context);
	     word != NULL;
	     word = strtok_r(NULL, " ", &context)) {

		if (nargs >= MAXMENUARGS) {
			printf("Command line has too many words.\n");
			return E2BIG;
		}
		args[nargs++] = word;
	}

	if (nargs==0) {
		return 0;
	}

	for (i=0; cmdtable[i].name; i++) {
		if (*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
			assert(cmdtable[i].func!=NULL);
            
            /* Call function through the cmd_table */
			result = cmdtable[i].func(nargs, args);
			return result;
		}
	}

	printf("%s: Command not found. Use 'help' command for a list of commands.\n", args[0]);
	return EINVAL;
}

int commandLineLoop()
{
    char *buffer;
    size_t bufsize = 64;

    buffer = (char*) malloc(bufsize * sizeof(char));
    if (buffer == NULL) {
        perror("Unable to malloc buffer.");
        exit(1);
    }

    printf("Welcome to CSUBatch.\n");

    // Main loop
    while(1) {
        printf("Please enter your command. Type 'help' for a list of commands.\n");
        getline(&buffer, &bufsize, stdin);
        cmd_dispatch(buffer);
    }

    return 0;
}