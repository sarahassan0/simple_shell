#include "shell.h"

/**
 * remove_comments - Removes comments from a command line input.
 * @lineptr: Pointer to the string containing the command line input.
 *
 * Return: Pointer to a newly allocated string without the comments,
 *         NULL if lineptr is NULL or an empty string.
 */

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

/*
char *_strdup(char *str)
{

	char *ptr;
	int i, size = 0;

	if (str == NULL)
	{
		return (NULL);
	}

	while (str[size] != '\0')
	{
		size++;
	}
	ptr = (char *)malloc(sizeof(char) * (size + 2));
	if (ptr == NULL)
	{
		free(str);
		return (NULL);
	}
	for (i = 0; i <= size; i++)
	{
		ptr[i] = str[i];
	}
	// free(str);
	return (ptr);
}
*/

int _strlen(char *s)
{
	int len;

	len = 0;
	if (s[0] == '\0')
		return (0);

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}
char *_strdup(char *str)
{
	int len;
	char *arr;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	arr = malloc((sizeof(char) * len) + 1);
	if (arr == NULL)
		return (NULL);
	arr[len] = '\0';
	while (len--)
		arr[len] = str[len];
	return (arr);
}

int _strcmp(char *s1, char *s2)
{
	while (((*s1 != '\0') && (*s2 != '\0')) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
	{
		return (0);
	}

	else
	{
		return (*s1 - *s2);
	}
}
