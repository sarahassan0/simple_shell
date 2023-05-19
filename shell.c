#include "shell.h"

/**
 * main - simple shell program imitates some bash shell features.
 * @argc: number of arguments.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
char **shell_args;

int main(int argc, __attribute__((unused)) char *argv[])
{
	shell_args = argv;
	signal(SIGINT, handler);
	if (argc > 1)
	{
		printf("file\n");
		/* read_file()*/
		return (0);
	}

	check_interactive(argv);

	return (0);
}

/**
 * check_interactive - check shell mode.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
int check_interactive(char **argv)
{
	if (argv == NULL)
		return (-1);
	if (isatty(STDIN_FILENO) > 0)
		return (is_interactive());
	else
		return (is_not_inreractive(argv));
}

/**
 * is_interactive - launch shell in interactive mode.
 *
 * Return: 0 on success
 */
int is_interactive(void)
{
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t read;
	char *str = NULL;
	char **cmd = NULL;

	printf("$ ");
	while ((read = getline(&lineptr, &len, stdin)) != -1)
	{
		if (read > 1)
		{
			lineptr[read - 1] == '\n' ? lineptr[read - 1] = '\0' : 0;

			str = remove_comments(lineptr);
			printf("test after removing comments: %s\n", str);
			cmd = split_cmd(str);
			printf("test the command: %s\n", cmd[0]);
			check_cmd(cmd);
		}
		printf("$ ");
	}
	free(cmd);
	free(lineptr);
	return (0);
}

/**
 * is_not_inreractive -  launch shell in non-interactive mode.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
int is_not_inreractive(char **argv)
{

	printf("pipe, %s\n", argv[0]);
	return (0);
}

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
		// exit(EXIT_SUCCESS);
	}
}
