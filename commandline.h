/*
Header for commandline.c"
*/
#ifndef COMMANDLINE
#define COMMANDLINE

// Definitions
#define EINVAL  1 // Error: Invalid
#define E2BIG   2 // Error: Too Big
#define MAXMENUARGS 4 // Max number of arguments on cmd line
#define MAXCMDLINE  64 // Max numbers of characters on cmd line
// For submitting jobs
#define DEFAULTEXECTIME 15; 
#define DEFAULTPRIORITY 1; 

void menu_execute(char *line, int isargs);
int cmd_run(int nargs, char **args);
int cmd_quit(int nargs, char **args);
int cmd_list(int nargs, char **args);
int cmd_fcfs(int nargs, char **args);
int cmd_sjf(int nargs, char **args);
int cmd_priority(int nargs, char **args);
int cmd_test(int nargs, char **args);
void showmenu(const char *x[]);
int cmd_helpmenu(int n, char **a);
int cmd_dispatch(char *cmd);
int commandLineLoop();
#endif