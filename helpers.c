#include "shell.h"

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
        char **new_path;

        path_env = getenv("PATH");
        if (path_env == NULL)
                return (NULL);
        path_cpy = strdup(path_env);
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
                new_path = realloc(PATH, (i + 2) * sizeof(char *));
                if (new_path == NULL)
                {
                        free_arr(PATH);
                        free(path_cpy);
                        return (NULL);
                }
                PATH = new_path;
                PATH[i] = strdup(token);

                if (PATH[i] == NULL)
                {
                        free_arr(PATH);
                        free(path_cpy);
                        free_arr(PATH);
                        return (NULL);
                }
                token = strtok(NULL, ":");
                i++;
        }

        PATH[i] = NULL;
        free(path_cpy);
        return (PATH);
}

void error_handler(char *program, int cmd_counter, char *cmd, int error_type)
{
        char *counter;

        counter = num_to_char(cmd_counter);
        write(STDERR_FILENO, program, strlen(program));
        write(STDERR_FILENO, ": ", 2);
        write(STDERR_FILENO, counter, strlen(counter));
        write(STDERR_FILENO, ": ", 2);
        if (error_type == EXIT_ERR)
        {
                write(STDERR_FILENO, "exit: ", 7);

                write(STDERR_FILENO, "Illegal number: ", 16);
                write(STDERR_FILENO, cmd, strlen(cmd));
                write(STDERR_FILENO, "\n", 1);
        }
        else if (error_type == PERMISSION_ERR)
        {
                perror(cmd);
        }
        else if (error_type == NOT_FOUND_ERR)
        {
                write(STDERR_FILENO, cmd, strlen(cmd));
                write(STDERR_FILENO, ": ", 2);

                write(STDERR_FILENO, "not found\n", 10);
        }
        free(counter);
}
