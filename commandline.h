/*
Header for commandline.c"
*/
#ifndef COMMANDLINE
#define COMMANDLINE

void menu_execute(char *line, int isargs);
int cmd_run(int nargs, char **args);
int cmd_quit(int nargs, char **args);
void showmenu(const char *x[]);
int cmd_helpmenu(int n, char **a);
int cmd_dispatch(char *cmd);
int commandLineLoop();
#endif