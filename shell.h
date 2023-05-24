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

/* Macros */
#define PERMISSION_ERR 126
#define NOT_FOUND_ERR 127
#define EXIT_ERR 2
extern char **environ;

/* Structs */

/**
 * struct global - struct for global info
 * @argv:pointer to array of argv.
 * @env: pointer to array of environment variables.
 * @cmd: pointer to array of splitted command.
 * @cmds_counter: commands counter.
 * @final_status: final exit status of the shell
 *
 * Description:  struct for global info of the shell
 */
typedef struct global
{
	char **argv;
	char **env;
	char **cmd;
	int cmds_counter;
	int final_status;

} global_t;

/* Functions */
int check_interactive(global_t *shell_info);
int is_interactive(global_t *shell_info);
int is_not_interactive(global_t *shell_info);

/* Excute functions */
int check_cmd(global_t *shell_info);
int external_cmd(global_t *shell_info);
int exec_external(char *cmd_path, global_t *shell_info);
int exec_path(global_t *shell_info);
int exec_file(global_t *shell_info);
void exec_child(char *cmd_path, global_t *shell_info);

/* Helper functions */
void free_arr(char **arr);
char **find_path_env();
int read_buff(global_t *shell_info, int fd);
void handler(int sg);
int error_handler(global_t *shell_info, int error_type);
int is_path(char **cmd);

/* string functions */
char *remove_comments(char *lineptr);
char **split_cmd(char *str);
char *_strdup(char *str);
int _atoi(char *s);
char *num_to_char(int num);

/* built-in commands*/
int exit_cmd(global_t *shell_info);
int print_env(global_t *shell_info);
int cd_cmd(global_t *shell_info);

#endif
