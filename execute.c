#include "shell.h"

/**
 * check_cmd -  check if the command is built-in or external command.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on failure.
 */

int check_cmd(char **cmd, char **argv, int cmds_counter)
{
	int i;
	char *builtin_cmd[] = {"exit", NULL};

	int (*builtin_func[])(char **cmd, char **argv, int cmds_counter) = {
	    &exit_cmd};
	i = 0;

	if (cmd == NULL || *cmd == NULL)
	{
		free_arr(cmd);
		return (1);
	}
	while (builtin_cmd[i] != NULL)
	{
		if (strcmp(cmd[0], builtin_cmd[i]) == 0)
		{
			return ((*builtin_func[i])(cmd, argv, cmds_counter));
		}
		i++;
	}
	return (external_cmd(cmd, argv, cmds_counter));
}

/**
 * external_cmd -  check the access of external command program.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on failure.
 */

int external_cmd(char **cmd, char **argv, int cmds_counter)
{

	if (cmd == NULL)
		return (1);

	if (access(cmd[0], F_OK) == 0)
	{
		printf("%s excutable command\n", cmd[0]);
		return (exec_external(cmd[0], cmd, argv, cmds_counter));
	}
	else

		return (exec_path(cmd, argv, cmds_counter));
}

int exec_path(char **cmd, char **argv, int cmds_counter)
{
	char **PATH;
	int i = 0;
	char *cmd_path;
	PATH = find_path_env();

	if (PATH == NULL)
	{
		free_arr(cmd);
		return (1);
	}
	/* check if cmd progam present in PATH env excute the cmd  */
	while (PATH[i] != NULL && PATH != NULL)
	{
		cmd_path = malloc(strlen(PATH[i]) + strlen(cmd[0]) + 2);
		if (cmd_path == NULL)
		{
			free(PATH);
			free_arr(cmd);
			// free(cmd_path);
			return (1);
		}
		sprintf(cmd_path, "%s/%s", PATH[i], cmd[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free_arr(PATH);
			// printf("%s excutable command\n", cmd_path);
			return (exec_external(cmd_path, cmd, argv, cmds_counter));
		}
		free(cmd_path);
		i++;
	}
	/* if doesnt print err*/
	error_handler(argv[0], cmds_counter, cmd[0], NOT_FOUND_ERR);
	free_arr(cmd);
	free_arr(PATH);
	return (127);
}

/**
 * exec_external -  excute external commands.
 * @cmd_path: command's path.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on error.
 */
int exec_external(char *cmd_path, char **cmd, char **argv, int cmds_counter)
{
	pid_t pid;
	int status;

	if (cmd_path == NULL || cmd == NULL)
	{
		if (cmd_path != cmd[0])
			free(cmd_path);
		free_arr(cmd);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(cmd[0]);
		if (cmd_path != cmd[0])
			free(cmd_path);
		free_arr(cmd);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("%s excutable \n", cmd_path);

		exec_child(cmd_path, cmd, argv, cmds_counter);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("wait");
		if (cmd_path != cmd[0])
			free(cmd_path);
		free_arr(cmd);
		exit(EXIT_FAILURE);
	}
	if (cmd_path != cmd[0])
		free(cmd_path);
	free_arr(cmd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (WTERMSIG(status));
}

void exec_child(char *cmd_path, char **cmd, char **argv, int cmds_counter)
{
	if (execve(cmd_path, cmd, NULL) == -1)
	{
		printf("%s excutable command\n", cmd_path);

		error_handler(argv[0], cmds_counter, cmd_path, PERMISSION_ERR);
		if (cmd_path != cmd[0])
			free(cmd_path);
		// free(cmd_path);
		free_arr(cmd);

		exit(EXIT_FAILURE);
	}
	printf("%s excutable mand\n", cmd_path);

	exit(EXIT_SUCCESS);
}

// int is_path(char **cmd)
// {
// 	int i = 0;
// 	while (cmd[0][i] != '\0')
// 	{
// 		if (cmd[0][i] == '/')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
