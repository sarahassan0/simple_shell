#include "shell.h"

int exit_cmd(char **cmd, char **argv, int cmds_counter)
{
	int status;
	if (cmd == NULL || cmd[0] == NULL)
	{

		free_arr(cmd);
		return 0;
	}
	if (cmd[1])
	{
		// hande non number strinds
		status = atoi(cmd[1]);
		if (status <= 999999999)
		{
			printf("nnnnnnnn%d\n", status);
			free_arr(cmd);
			exit(status);
		}
		else
		{
			error_handler(argv[0], cmds_counter, cmd[1], EXIT_ERR);
			free_arr(cmd);
			return (2);
		}
	}

	free_arr(cmd);
	exit(0);
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
