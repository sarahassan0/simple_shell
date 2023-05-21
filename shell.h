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

#define PERMISSION_ERR 126
#define NOT_FOUND_ERR 127
#define EXIT_ERR 2

int check_interactive(char **argv, int cmds_counter);
int is_interactive(char **argv, int cmds_counter);
int is_not_inreractive(char **argv, int cmds_counter);
char *remove_comments(char *lineptr);
char **split_cmd(char *str);
char *_strdup(char *str);
void free_arr(char **arr);
int check_cmd(char **cmd, char **argv, int cmds_counter);
int external_cmd(char **cmd, char **argv, int cmds_counter);
char **find_path_env();
int exec_external(char *cmd_path, char **cmd, char **argv, int cmds_counter);
void handler(int sg);
// extern char **shell_args;
// int is_path(char **cmd);
int exec_path(char **cmd, char **argv, int cmds_counter);
int exit_cmd(char **cmd, char **argv, int cmds_counter);
int read_file(char **argv);
char *num_to_char(int num);
void error_handler(char *program, int cmd_counter, char *cmd, int error_type);
void exec_child(char *cmd_path, char **cmd, char **argv, int cmds_counter);

// char *read_stream(void)

#endif
