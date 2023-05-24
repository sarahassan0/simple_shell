#include "shell.h"

/**
 * handler -  handel the signal.
 * @sg: signal int.
 *
 * Return: void.
 */
void handler(int __attribute__((unused)) sg)
{
	if (sg == SIGINT)
	{
		write(1, "\n$ ", 3);
	}
}

/**
 * read_buff - Read a line of input from a file descriptor.
 * @shell_info: Pointer to the global shell information.
 * @fd: The file descriptor to read from.
 *
 * Return: Number of final_status.
 */

int read_buff(global_t *shell_info, int fd)
{
	char buffer[10000];
	ssize_t n_bytes;
	char *str = NULL, *line = NULL;
	char *lines[1000];
	int i, lineCount = 0;

	memset(buffer, 0, sizeof(buffer));

	n_bytes = read(fd, buffer, sizeof(buffer));
	if (n_bytes < 0)
	{
		perror("read");
		exit(0);
	}
	line = strtok(buffer, "\n");
	while (line != NULL && lineCount < (int)(sizeof(lines) / sizeof(lines[0])))
	{
		lines[lineCount] = strdup(line);
		if (lines[lineCount] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}

		lineCount++;
		line = strtok(NULL, "\n");
	}
	for (i = 0; i < lineCount; i++)
	{
		shell_info->cmds_counter++;
		str = remove_comments(lines[i]);
		shell_info->cmd = split_cmd(str);
		shell_info->final_status = check_cmd(shell_info);
		free(lines[i]);
	}

	return (shell_info->final_status);
}

/**
 * find_path_env-  find the absluote path of a command.
 *
 * Return: the command's path.
 */

char **find_path_env(void)
{
	char *path_env, *path_cpy, *token;
	char **PATH;
	int i = 0;
	char **new_path;

	path_env = getenv("PATH");
	path_cpy = strdup(path_env);
	PATH = malloc(sizeof(char *));
	if (path_env == NULL || path_cpy == NULL || PATH == NULL)
		return (NULL);

	token = strtok(path_cpy, ":");
	while (token != NULL)
	{
		new_path = realloc(PATH, (i + 2) * sizeof(char *));
		if (new_path == NULL)
		{
			free_arr(PATH);
			free(path_cpy);
			return (NULL);
		}
		PATH = new_path;
		PATH[i] = strdup(token);

		if (PATH[i] == NULL)
		{
			free_arr(PATH);
			free(path_cpy);
			free_arr(PATH);
			return (NULL);
		}
		token = strtok(NULL, ":");
		i++;
	}

	PATH[i] = NULL;
	free(path_cpy);
	return (PATH);
}

/**
 * error_handler - Handle and display shell errors.
 * @shell_info: Pointer to the global shell information.
 * @error_type: The type of error to handle.
 *
 * Return: 0 on sucsess.
 */

int error_handler(global_t *shell_info, int error_type)
{
	char *counter;

	counter = num_to_char(shell_info->cmds_counter);
	write(STDERR_FILENO, shell_info->argv[0], strlen(shell_info->argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter, strlen(counter));
	write(STDERR_FILENO, ": ", 2);
	if (error_type == EXIT_ERR)
	{
		write(STDERR_FILENO, shell_info->cmd[0], strlen(shell_info->cmd[0]));
		write(STDERR_FILENO, ": ", 2);
		if (strlen(shell_info->cmd[0]) == 2)
			write(STDERR_FILENO, "can't cd to ", 12);
		else
			write(STDERR_FILENO, "Illegal number: ", 16);

		write(STDERR_FILENO, shell_info->cmd[1], strlen(shell_info->cmd[1]));
		write(STDERR_FILENO, "\n", 1);
		free(counter);
		return (EXIT_ERR);
	}
	else if (error_type == PERMISSION_ERR)
	{
		perror(shell_info->cmd[0]);
		free(counter);
		return (PERMISSION_ERR);
	}
	else if (error_type == NOT_FOUND_ERR)
	{
		write(STDERR_FILENO, shell_info->cmd[0], strlen(shell_info->cmd[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "not found\n", 10);
		free(counter);
		return (NOT_FOUND_ERR);
	}
	free(counter);
	free(shell_info);
	return (0);
}

/**
 * is_path - covert number to string.
 * @cmd: string to be converted to number.
 *
 * Return: 1 if path, 0 if not.
 */
int is_path(char **cmd)
{
	int i = 0;

	while (cmd[0][i] != '\0')
	{
		if (cmd[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}
