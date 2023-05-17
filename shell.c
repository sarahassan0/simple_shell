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
 * is_interactive -  launch shell in interactive mode.
 *
 * Return: 0 on success
 */
int is_interactive(void)
{
	printf("$\n");
	return (0);
}

/**
 * is_not_interactive -  launch shell in non-interactive mode.
 * @argv: pointer to an array of arguments.
 *
 * Return: 0 on success
 */
int is_not_inreractive(char **argv)
{

	printf("pipe, %s\n", argv[0]);
	return (0);
}
