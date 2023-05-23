#include "shell.h"

int exit_cmd(global_t *shell_info)
{
	int status;
	if (shell_info == NULL)
	{

		// free_arr(cmd);
		return 0;
	}
	if (shell_info->cmd[1])
	{
		// hande non number strinds
		status = _atoi(shell_info->cmd[1]);
		if (status == -1)
		{
			shell_info->final_status = error_handler(shell_info, EXIT_ERR);
			// free_arr(shell_info->cmd);
		}
		else
		{
			// free_arr(shell_info->cmd);
			exit(status);
		}
		// else
		// {
		// 	error_handler(shell_info, EXIT_ERR);
		// 	free_arr(shell_info->cmd);
		// 	error_handler(shell_info, EXIT_ERR);
		// }
	}
	free_arr(shell_info->cmd);
	exit(shell_info->final_status);
}

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

// int cd_func(__attribute__((unused)) char **cmd)
// {
//      if (chdir(cmd[1]) != 0)
//     {
//         perror(cmd[1]);
//         return (-1);
//     }

//     return (0);
// }
