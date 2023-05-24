#include "shell.h"

/**
 * main - simple shell program imitates some bash shell features.
 * @argc: number of arguments.
 * @argv: pointer to an array of arguments.
 * @env: pointer to an array of env.
 *
 * Return: 0 on success
 */

int main(int argc, char **argv, char **env)
{
	global_t *shell_info;
	int status;

	shell_info = malloc(sizeof(global_t));
	shell_info->argv = argv;
	shell_info->env = env;
	shell_info->cmd = NULL;
	shell_info->cmds_counter = 0;
	shell_info->final_status = 0;

	signal(SIGINT, handler);
	if (argc > 1)
	{
		exec_file(shell_info);
		return (0);
	}
	status = check_interactive(shell_info);
	free(shell_info);
	return (status);
}

/**
 * check_interactive - check shell mode.
 * @shell_info: pointer to struct of shell info.
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
 * @shell_info: pointer to struct of shell info.
 *
 * Return: 0 on success
 */
int is_interactive(global_t *shell_info)
{
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t read;
	char *str = NULL;

	printf("$ ");
	while ((read = getline(&lineptr, &len, stdin)) != -1)
	{
		if (read > 1)
		{
			shell_info->cmds_counter++;
			lineptr[read - 1] == '\n' ? lineptr[read - 1] = '\0' : 0;

			str = remove_comments(lineptr);
			shell_info->cmd = split_cmd(str);

			shell_info->final_status = check_cmd(shell_info);
		}
		printf("$ ");
	}

	free(lineptr);
	return (shell_info->final_status);
}

/**
 * is_not_interactive - launch shell in non-interactive mode.
 * @shell_info: pointer to struct of shell info.
 *
 * Return: 0 on success
 */
int is_not_interactive(global_t *shell_info)
{
	return (read_buff(shell_info, 0));
}

/**
 * exec_file - Execute a file as a shell script.
 * @shell_info: Pointer to the global shell information.
 *
 * Return: 0 on success, or -1 on failure.
 */
int exec_file(global_t *shell_info)
{
	int fd;

	fd = open(shell_info->argv[1], O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (read_buff(shell_info, fd));
}
