#include "shell.h"

char *remove_comments(char *lineptr)
{
        int i = 0, len = 0;
        char *str = NULL;

        if (lineptr == NULL || *lineptr == '\0')
        {
                return (NULL);
        }
        if (lineptr[0] == '#')
                return (0);

        len = _strlen(lineptr);
        str = malloc(len + 1);
        if (str == NULL)
        {
                return (NULL);
        }

        while (lineptr[i] != '\0' && lineptr[i] != '\n')
        {
                if (lineptr[i] == ' ' && lineptr[i + 1] == '#')
                {
                        break;
                }
                str[i] = lineptr[i];
                i++;
        }
        str[i] = '\0';
        return (str);
}

/**
 * split_cmd - Splits a string into an array of words based on a delimiter.
 * @str: Pointer to the string to be split.
 *
 * Return: Dynamically allocated array of strings (words) obtained by splitting
 *         the input string, NULL if str is NULL or memory allocation fails.
 */

char **split_cmd(char *str)
{
        char **words;
        char *delim = " ";
        char *token;
        int i = 0;

        if (str == NULL)
                return (NULL);
        words = malloc(sizeof(char *));
        if (words == NULL)
        {
                free(str);
                return (NULL);
        }
        token = strtok(str, delim);
        while (token != NULL)
        {
                char **new_arr = realloc(words, (i + 2) * sizeof(char *));

                if (new_arr == NULL)
                {
                        free(str);
                        free_arr(words);
                        return (NULL);
                }
                words = new_arr;
                words[i] = _strdup(token);
                if (words[i] == NULL)
                {
                        free(str);
                        free_arr(words);
                        return (NULL);
                }
                token = strtok(NULL, delim);
                i++;
        }
        words[i] = '\0';
        free(str);
        return (words);
}

char *_getenv(char *name)
{
        int i = 0, j = 0;

        if (name == NULL)
                return (NULL);
        while (environ[i])
        {
                j = 0;
                while (environ[i][j] != '=')
                {
                        if (environ[i][j] != name[j])
                                break;
                        if (environ[i][j] == name[j] && (environ[i][j + 1] == '='))
                                return (&environ[i][_strlen(name) + 1]);
                        j++;
                }
                i++;
        }
        return (NULL);
}

/**
 * free_arr - Free the memory allocated for an array of strings.
 * @arr: Pointer to the array of strings to be freed.
 */

void free_arr(char **arr)
{
        int i;

        if (arr == NULL)
                return;
        for (i = 0; arr[i] != NULL; i++)
                free(arr[i]);

        free(arr);
}

#include <stdarg.h>

int _sprintf(char *str, const char *format, ...)
{
        int count = 0, i;
        va_list args;
        va_start(args, format);

        while (*format != '\0')
        {
                if (*format == '%')
                {
                        format++;
                        if (*format == 'd')
                        {
                                int num = va_arg(args, int);
                                int numDigits = 0;
                                int temp = num;
                                while (temp != 0)
                                {
                                        numDigits++;
                                        temp /= 10;
                                }
                                for (i = numDigits - 1; i >= 0; i--)
                                {
                                        str[count++] = '0' + (num % 10);
                                        num /= 10;
                                }
                        }
                        else if (*format == 's')
                        {
                                char *strArg = va_arg(args, char *);
                                while (*strArg != '\0')
                                {
                                        str[count++] = *strArg++;
                                }
                        }
                        else
                                return -1;
                }
                else
                {
                        str[count++] = *format;
                }
                format++;
        }
        str[count] = '\0';
        va_end(args);
        return count;
}
