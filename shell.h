#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

int check_interactive(char **argv);
int is_interactive(void);
int is_not_inreractive(char **argv);
char *remove_comments(char *lineptr);
char **split_cmd(char *str);
char *_strdup(char *str);
void free_arr(char **arr);
int check_cmd(char **cmd);
int external_cmd(char **cmd);
char **find_path_env();
int exec_external(char *cmd_path, char **cmd, int is_path);
void handler(int sg);
extern char **shell_args;
int is_path(char **cmd);

#endif
