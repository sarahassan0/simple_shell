#include "shell.h"

/**
 * check_cmd -  check if the command is built-in or external command.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on failure.
 */
// pid_t pid;
int check_cmd(global_t *shell_info)
{
	// printf("%s gggggggggggggg", shell_info->cmd[0]);

	int i;
	char *builtin_cmd[] = {"exit", "env", NULL};

	int (*builtin_func[])(global_t *shell_info) = {
	    &exit_cmd, &print_env};
	i = 0;

	// printf("%s wwwwwwwwwwwww", shell_info->cmd[0]);
	if (shell_info->cmd == NULL || shell_info->cmd[0] == NULL)
	{
		free_arr(shell_info->cmd);
		return (0);
	}

	while (builtin_cmd[i] != NULL)
	{
		if (strcmp(shell_info->cmd[0], builtin_cmd[i]) == 0)
		{
			return ((*builtin_func[i])(shell_info));
		}
		i++;
	}
	// printf("%s wwwwwwwwwwwww", shell_info->cmd[0]);

	return (external_cmd(shell_info));
}

/**
 * external_cmd -  check the access of external command program.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on failure.
 */

int external_cmd(global_t *shell_info)
{
	// printf("%s wwwwwwwwwwwww", shell_info->cmd[0]);

	if (shell_info == NULL)
		return (0);

	if (access(shell_info->cmd[0], F_OK) == 0)
	{
		// printf("%s excutable command\n", cmd[0]);
		return (exec_external(shell_info->cmd[0], shell_info));
	}
	else

		return (exec_path(shell_info));
}

int exec_path(global_t *shell_info)
{
	char **PATH;
	int i = 0;
	char *cmd_path;
	PATH = find_path_env();

	if (PATH == NULL)
	{
		free_arr(shell_info->cmd);
		return (1);
	}
	/* check if cmd progam present in PATH env excute the cmd  */
	// printf("%s excutable command\n", shell_info->cmd[0]);

	while (PATH[i] != NULL && PATH != NULL)
	{
		cmd_path = malloc(strlen(PATH[i]) + strlen(shell_info->cmd[0]) + 2);
		if (cmd_path == NULL)
		{
			free(PATH);
			free_arr(shell_info->cmd);
			// free(cmd_path);
			return (0);
		}
		sprintf(cmd_path, "%s/%s", PATH[i], shell_info->cmd[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free_arr(PATH);
			// printf("%s excutable command\n", cmd_path);
			return (exec_external(cmd_path, shell_info));
		}
		i++;
		free(cmd_path);
	}
	// printf("%s excutable command\n", shell_info->cmd[0]);

	if (access(shell_info->cmd[0], F_OK) == 0)
	{
		// printf("%s excutable command\n", cmd_path);
		return (exec_external(shell_info->cmd[0], shell_info));
	}
	/* if doesnt print err*/
	int status = error_handler(shell_info, NOT_FOUND_ERR);

	free_arr(shell_info->cmd);
	free_arr(PATH);
	return (status);
}

/**
 * exec_external -  excute external commands.
 * @cmd_path: command's path.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on error.
 */
int exec_external(char *cmd_path, global_t *shell_info)
{
	pid_t pid;
	int status;

	if (cmd_path == NULL || shell_info == NULL)
	{
		if (cmd_path != shell_info->cmd[0])
			free(cmd_path);
		free_arr(shell_info->cmd);
		return (0);
	}
	pid = fork();

	if (pid == -1)
	{
		perror(shell_info->cmd[0]);
		if (cmd_path != shell_info->cmd[0])
			free(cmd_path);
		free_arr(shell_info->cmd);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// printf("%s excutable \n", cmd_path);
		// signal(SIGINT, handler);

		exec_child(cmd_path, shell_info);
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("wait");
		if (cmd_path != shell_info->cmd[0])
			free(cmd_path);
		free_arr(shell_info->cmd);
		exit(EXIT_FAILURE);
	}
	if (cmd_path != shell_info->cmd[0])
		free(cmd_path);
	free_arr(shell_info->cmd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (WTERMSIG(status));
}

void exec_child(char *cmd_path, global_t *shell_info)
{
	int status = 0;
	if (execve(cmd_path, shell_info->cmd, shell_info->env) == -1)
	{

		status = error_handler(shell_info, PERMISSION_ERR);
		if (cmd_path != shell_info->cmd[0])
			free(cmd_path);
		free_arr(shell_info->cmd);
		exit(status);
	}

	exit(status);
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
