#include "shell.h"



/**
 * print_env - Print the environment variables.
 * @shell_info: Pointer to the global shell information.
 *
 * Return: 0 on success.
 */

int print_env(global_t *shell_info)
{
	int i;

	i = 0;
	if (shell_info->env == NULL)
	{
		free_arr(shell_info->cmd);
		return (EXIT_ERR);
	}

	while (shell_info->env[i] != NULL)
	{
		printf("%s\n", shell_info->env[i]);
		i++;
	}
	free_arr(shell_info->cmd);
	return (0);
}

/**
 * cd_cmd - Change the current working directory.
 * @shell_info: Pointer to the global shell information struct.
 *
 * Return: 0 on success, -1 on failure.
 */

int cd_cmd(global_t *shell_info)
{
	if (shell_info->cmd[1] == NULL)
	{
		return (0);
	}
	if (chdir(shell_info->cmd[1]) == -1)
	{
		return (error_handler(shell_info, EXIT_ERR));
	}

	return (0);
}
