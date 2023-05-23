#include "shell.h"

/**
 * main - simple shell program imitates some bash shell features.
 * @argc: number of arguments.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */

int main(int argc, __attribute__((unused)) char **argv, char **env)
{
	global_t *shell_info;
	int status;

	shell_info = malloc(sizeof(global_t));
	shell_info->argv = argv;
	shell_info->env = env;
	shell_info->cmd = NULL;
	shell_info->cmds_counter = 0;

	signal(SIGINT, handler);

	// status = check_interactive(shell_info);
	// shell_info->final_status = check_interactive(shell_info);
	if (argc > 1)
	{
		exec_file(shell_info);
		return (0);
	}
	status = check_interactive(shell_info);
	// free_arr(shell_info->cmd);
	free(shell_info);
	return (status);
}

/**
 * check_interactive - check shell mode.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
int check_interactive(global_t *shell_info)
{

	if (shell_info == NULL)
		return (-1);
	if (isatty(STDIN_FILENO) > 0)
		return (is_interactive(shell_info));
	else
		return (is_not_interactive(shell_info));
}

/**
 * is_interactive - launch shell in interactive mode.
 *
 * Return: 0 on success
 */
int is_interactive(global_t *shell_info)

{
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t read;
	char *str = NULL;
	// char **cmd = NULL;
	// int status;

	printf("$ ");
	while ((read = getline(&lineptr, &len, stdin)) != -1)
	{
		if (read > 1)
		{
			shell_info->cmds_counter++;

			lineptr[read - 1] == '\n' ? lineptr[read - 1] = '\0' : 0;

			str = remove_comments(lineptr);
			// printf("test after removing comments: %s\n", str);
			shell_info->cmd = split_cmd(str);
			// printf("%s innnnnnnn", shell_info->cmd[0]);

			shell_info->final_status = check_cmd(shell_info);

			// if (check_cmd(cmd, argv, cmds_counter) == 127)
			// {

			// free(lineptr);
			// }
			// printf("sssssssssssss :%d\n", status);
			// printf("eeeeeeeeeee :%d\n", status_exit);
		}
		// free(lineptr);
		printf("$ ");
	}
	// if (read == -1)
	// {
	// 	free(lineptr);
	// 	// return the last status
	// 	return status;
	// }
	free(lineptr);

	// free(str);
	return (shell_info->final_status);
}

/**
 * is_not_inreractive -  launch shell in non-interactive mode.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
int is_not_interactive(global_t *shell_info)
{
	return read_buff(shell_info, 0);
}

int exec_file(global_t *shell_info)
{
	int fd;
	fd = open(shell_info->argv[1], O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return read_buff(shell_info, fd);
}
