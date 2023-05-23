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

typedef struct global
{
        char **argv;
        char **env;
        char **cmd;
        int cmds_counter;
        int final_status;
        // pid_t child_pid;

} global_t;
int check_interactive(global_t *shell_info);
int is_interactive(global_t *shell_info);
int is_not_interactive(global_t *shell_info);
char *remove_comments(char *lineptr);
char **split_cmd(char *str);
char *_strdup(char *str);
void free_arr(char **arr);
int check_cmd(global_t *shell_info);
int external_cmd(global_t *shell_info);
char **find_path_env();
int exec_external(char *cmd_path, global_t *shell_info);
void handler(int sg);
// extern char **shell_args;
// int is_path(char **cmd);
int exec_path(global_t *shell_info);
int read_file(char **argv);
char *num_to_char(int num);
int error_handler(global_t *shell_info, int error_type);
void exec_child(char *cmd_path, global_t *shell_info);
int _atoi(char *s);

/* built-in commands*/
int exit_cmd(global_t *shell_info);
int print_env(global_t *shell_info);

extern pid_t pid;
extern int status_exit;

// char *read_stream(void)

#endif
