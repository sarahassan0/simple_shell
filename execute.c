#include "shell.h"

// char *builtin_cmd[] = {"cd", "ls", "exit"};
// int (*builtin_func[])(char **) = {
//     &cd_func
// };

/**
 * check_cmd -  check if the command is built-in or external command.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on failure.
 */

int check_cmd(char **cmd)
{

	// int i = 0;
	if (cmd == NULL || *cmd == NULL)
		return (1);

	// while (builtin_cmd[i] != NULL)
	//     {

	//             if (strcmp(cmd[0], builtin_cmd[i]) == 0)
	//             {
	//                     // return ((*builtin_func[i])(cmd));

	//             }
	//             i++;
	//     }

	return (external_cmd(cmd));
}

/**
 * external_cmd -  check the access of external command program.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on failure.
 */
int is_path(char **cmd);

int external_cmd(char **cmd)
{
	char **PATH;
	int i = 0;
	char *cmd_path;
	struct stat st;

	if (!is_path(cmd))
	{
		PATH = find_path_env();

		while (PATH[i] != NULL && PATH != NULL)
		{
			cmd_path = malloc(strlen(PATH[i]) + strlen(cmd[0]) + 2);
			if (cmd_path == NULL)
				return (1);
			sprintf(cmd_path, "%s/%s", PATH[i], cmd[0]);
			if (stat(cmd_path, &st) == 0)
			{
				if (access(cmd_path, X_OK) == 0)
				{
					printf("%s excutable command\n", cmd_path);
					return (exec_external(cmd_path, cmd, 0));
				}
				write(2, shell_args[0], strlen(shell_args[0]));
				write(2, ": ", 2);
				perror(cmd_path);
				return (1);
			}

			i++;
		}
		write(2, cmd[0], strlen(cmd[0]));
		write(2, ": ", 2);
		write(2, "command not founddd\n", 19);
		return (1);
	}

	if (stat(cmd[0], &st) == 0)
	{
		/* check if the absolute path is exist and belongs to a file*/
		if (S_ISDIR(st.st_mode))
		{
			write(2, shell_args[0], strlen(shell_args[0]));
			write(2, ": ", 2);
			write(2, cmd[0], strlen(cmd[0]));
			write(2, ": is a directory\n", 17);
			return (1);
		}
		printf("%s accesacle abslu\n", cmd[0]);
		return (exec_external(cmd[0], cmd, 1));
	}

	/* if doesnt print err*/
	write(2, shell_args[0], strlen(shell_args[0]));
	write(2, ": ", 2);
	perror(cmd[0]);
	return (1);
}

/**
 * exec_external -  excute external commands.
 * @cmd_path: command's path.
 * @cmd: pointer to an array of comand options.
 *
 * Return: 1 on error.
 */
int exec_external(char *cmd_path, char **cmd, int is_path)
{
	pid_t pid;
	int status;

	if (cmd_path == NULL || *cmd_path == '\0')
		return (1);

	pid = fork();
	if (pid == -1)
	{
		perror(cmd[0]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmd, NULL) == -1)
		{
			write(2, shell_args[0], strlen(shell_args[0]));
			write(2, ": ", 2);
			perror(cmd[0]);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait");
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

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path_cpy = _strdup(path_env);
	if (path_cpy == NULL)
		return (NULL);

	PATH = malloc(sizeof(char *));
	if (PATH == NULL)
	{
		free(path_cpy);
		return (NULL);
	}

	token = strtok(path_cpy, ":");
	while (token != NULL)
	{
		PATH = realloc(PATH, (i + 2) * sizeof(char *));

		PATH[i] = _strdup(token);
		if (PATH[i] == NULL)
		{
			free_arr(PATH);
			free(path_cpy);
			return (NULL);
		}

		token = strtok(NULL, ":");
		i++;
	}
	PATH[i] = NULL;
	free(path_cpy);
	return (PATH);
}

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

/* i will move it to builin_cmd.c file*/
// int cd_func(__attribute__((unused)) char **cmd)
// {
//      if (chdir(cmd[1]) != 0)
//     {
//         perror(cmd[1]);
//         return (-1);
//     }

//     return (0);
// }
