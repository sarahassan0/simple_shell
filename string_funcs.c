#include "shell.h"

/**
 * remove_comments - Removes comments from a command line input.
 * @lineptr: Pointer to the string containing the command line input.
 *
 * Return: Pointer to a newly allocated string without the comments,
 *         NULL if lineptr is NULL or an empty string.
 */

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

	len = strlen(lineptr);
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
 * num_to_char - covert number to string.
 * @num: string to be converted to number.
 *
 * Return: string,
 */
char *num_to_char(int num)
{
	int c = 0, tmp = num;
	char *str_num;

	if (num == 0)
	{
		c = 1;
	}
	else
	{
		while (tmp != 0)
		{
			tmp /= 10;
			c++;
		}
	}

	str_num = malloc(sizeof(char) * (c + 1));
	if (!str_num)
	{
		perror("malloc");
		return (NULL);
	}
	str_num[c] = '\0';
	while (c != 0)
	{
		c--;
		str_num[c] = '0' + num % 10;
		num /= 10;
	}

	return (str_num);
}

/**
 * _atoi - covert string to number.
 * @s: string to be converted to number.
 *
 * Return: result of converting string to number, -1 on failure.
 */

int _atoi(char *s)
{
	unsigned int result, i;
	char sign;

	i = 0;
	result = 0;

	while (s[i] != '\0')
	{
		if (!((s[i] >= '0') && (s[i] <= '9')))
		{
			return (-1);
		}
		if (((s[i] >= '0') && (s[i] <= '9')))
		{
			result = (result * 10) + (s[i] - '0');
		}
		else if (s[i] == '+')
			sign++;

		i++;
	}

	return (result);
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
