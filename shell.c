#include "shell.h"

/**
 * main - simple shell program imitates some bash shell features.
 * @argc: number of arguments.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */

int main(int argc, __attribute__((unused)) char *argv[])
{
	int cmds_counter = 0;
	// if (argv != NULL)
	signal(SIGINT, handler);
	if (argc > 1)
	{
		printf("file\n");
		read_file(argv);
		return (0);
	}

	check_interactive(argv, cmds_counter);

	return (0);
}

/**
 * check_interactive - check shell mode.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
int check_interactive(char **argv, int cmds_counter)
{

	if (argv == NULL)
		return (-1);
	if (isatty(STDIN_FILENO) > 0)
		return (is_interactive(argv, cmds_counter));
	else
		return (is_not_inreractive(argv, cmds_counter));
}

/**
 * is_interactive - launch shell in interactive mode.
 *
 * Return: 0 on success
 */
int is_interactive(char **argv, int cmds_counter)
{
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t read;
	char *str = NULL;
	char **cmd = NULL;
	int status;

	printf("$ ");
	while ((read = getline(&lineptr, &len, stdin)) != -1)
	{
		if (read > 1)
		{
			cmds_counter++;

			lineptr[read - 1] == '\n' ? lineptr[read - 1] = '\0' : 0;

			str = remove_comments(lineptr);
			printf("test after removing comments: %s\n", str);
			cmd = split_cmd(str);
			check_cmd(cmd, argv, cmds_counter);

			// if (check_cmd(cmd, argv, cmds_counter) == 127)
			// {

			// 	free(lineptr);
			// }
		}
		// free(lineptr);
		printf("$ ");
	}
	if (read == -1)
	{
		free(lineptr);
		// return the last status
		return status;
	}
	free(lineptr);

	// free(str);
	return (0);
}

/**
 * is_not_inreractive -  launch shell in non-interactive mode.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
int is_not_inreractive(char __attribute__((unused)) * *argv, int __attribute__((unused)) cmds_counter)
{
	// char buffer[1024];
	// ssize_t bytesRead;

	// Read input from the pipe until there is no more data
	// while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
	// {
	// 	if (bytesRead < 0)
	// 	{
	// 		perror("read");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	buffer[bytesRead - 1] == '\n' ? buffer[bytesRead - 1] = '\0' : 0;
	// 	printf("%s", buffer);
	// 	// Process the input data here
	// 	// For demonstration, let's just print the input
	// 	write(STDOUT_FILENO, buffer, bytesRead);
	// 	printf("pipe, %s\n", argv[0]);
	// }

	return (0);
}

int read_file(char __attribute__((unused)) * *argv)
{
	printf("file");
	return (0);
}
