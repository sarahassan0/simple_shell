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



#endif
