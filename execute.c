#include "shell.h"

/**
 * check_cmd -  check if the command is built-in or external command.
 * @shell_info: pointer to struct of shell info.
 *
 * Return: 0 on sucsses.
 */
int check_cmd(global_t *shell_info)
{

	int i;
	char *builtin_cmd[] = {"exit", "env", "cd", NULL};

	int (*builtin_func[])(global_t *shell_info) = {
		&exit_cmd, &print_env, &cd_cmd};
	i = 0;

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
	return (external_cmd(shell_info));
}

/**
 * external_cmd -  check the access of external command program.
 * @shell_info: pointer to struct of shell info.
 *
 * Return: 0 on sucsses.
 */

int external_cmd(global_t *shell_info)
{
	if (shell_info == NULL)
		return (0);

	if (access(shell_info->cmd[0], F_OK) == 0)
	{
		return (exec_external(shell_info->cmd[0], shell_info));
	}
	else
		return (exec_path(shell_info));
}

/**
 * exec_path -  excute programs present in the PATH env.
 * @shell_info: pointer to struct of shell info.
 *
 * Return: 0 on sucsses.
 */
int exec_path(global_t *shell_info)
{
	char **PATH;
	int i = 0, status;
	char *cmd_path;

	PATH = find_path_env();
	if (PATH == NULL)
	{
		free_arr(shell_info->cmd);
		return (1);
	}
	/* check if cmd progam present in PATH env excute the cmd  */
	while (PATH[i] != NULL && PATH != NULL)
	{
		cmd_path = malloc(strlen(PATH[i]) + strlen(shell_info->cmd[0]) + 2);
		if (cmd_path == NULL)
		{
			free(PATH);
			free_arr(shell_info->cmd);
			return (0);
		}
		sprintf(cmd_path, "%s/%s", PATH[i], shell_info->cmd[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free_arr(PATH);
			return (exec_external(cmd_path, shell_info));
		}
		i++;
		free(cmd_path);
	}
	if (access(shell_info->cmd[0], F_OK) == 0)
	{
		return (exec_external(shell_info->cmd[0], shell_info));
	}
	status = error_handler(shell_info, NOT_FOUND_ERR);
	free_arr(shell_info->cmd);
	free_arr(PATH);
	return (status);
}

/**
 * exec_external -  excute external commands.
 * @cmd_path: command's string .
 * @shell_info: pointer to struct of shell info.
 *
 * Return: 0 on sucsses.
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

/**
 * exec_child - function to run the child process.
 * @cmd_path: command's string .
 * @shell_info: pointer to struct of shell info.
 *
 * Return: 0 on sucsses.
 */
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
