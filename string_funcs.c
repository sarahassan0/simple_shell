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
	// printf("%s\n", lineptr);

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
		// free(lineptr);
		return (NULL);
	}

	while (lineptr[i] != '\0' && lineptr[i] != '\n')
	{
		if (lineptr[i - 1] == ' ' && lineptr[i] == '#')
		{
			break;
		}
		str[i] = lineptr[i];
		i++;
		// }
	}
	// free(lineptr);
	str[i] = '\0';
	// printf("%s\n", str);

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
	// printf("%s\n", str);

	char **words;
	char *delim = " ";
	char *token;
	int i = 0;

	if (str == NULL)
		return NULL;
	// while (str[i] != '\0' && str[i] != '\n')
	// {

	// 	str[i] = lineptr[i];
	// 	i++;
	// }
	words = malloc(sizeof(char *));
	if (words == NULL)
	{
		free(str);
		return NULL;
	}
	token = strtok(str, delim);
	while (token != NULL)
	{

		char **new_arr = realloc(words, (i + 2) * sizeof(char *));
		if (new_arr == NULL)
		{
			free(str);
			free_arr(words);
			return NULL;
		}
		words = new_arr;

		words[i] = strdup(token);
		// printf("%s\n", str);
		if (words[i] == NULL)
		{
			free(str);
			free_arr(words);
			return NULL;
		}

		token = strtok(NULL, delim);
		i++;
	}
	words[i] = NULL;
	// printf("FFFFFFF");
	// printf("%s", words[0]);
	// printf("%s", words[1]);

	free(str);
	return words;
}

/**
 * _strdup - Returns a pointer to a newly allocated space in memory
 * and copies the given string.
 * @str: String to be duplicated.
 *
 * Return: Pointer to the duplicated string,
 * NULL if insufficient memory was available.
 */

// char *_strdup(char *str)
// {

// 	char *ptr;
// 	int i, size = 0;

// 	if (str == NULL)
// 	{
// 		return (NULL);
// 	}

// 	while (str[size] != '\0')
// 	{
// 		size++;
// 	}
// 	ptr = (char *)malloc(sizeof(char) * (size + 2));
// 	if (ptr == NULL)
// 	{
// 		free(str);
// 		return (NULL);
// 	}
// 	for (i = 0; i <= size; i++)
// 	{
// 		ptr[i] = str[i];
// 	}
// 	// free(str);
// 	return (ptr);
// }

/**
 * free_arr - Frees the memory allocated for an array of strings.
 * @arr: Array of strings to be freed.
 */

void free_arr(char **arr)
{
	int i;

	if (arr == NULL || arr[0] == NULL)
		return;
	for (i = 0; arr[i] != NULL; i++)
		free(arr[i]);

	free(arr);
}

char *num_to_char(int num)
{
	/*count digits*/
	int c = 0, tmp = num;
	char *cp_num;
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

	cp_num = malloc(sizeof(char) * (c + 1));
	if (!cp_num)
	{
		perror("malloc");
		return (NULL);
	}
	cp_num[c] = '\0';
	while (c != 0)
	{
		c--;
		cp_num[c] = '0' + num % 10;
		num /= 10;
	}

	return (cp_num);
}
int _atoi(char *s)
{
	unsigned int n, i;
	char positive;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (!((s[i] >= '0') && (s[i] <= '9')))
		{
			return (-1);
		}
		if (((s[i] >= '0') && (s[i] <= '9')))
		{
			n = (n * 10) + (s[i] - '0');
		}
		else if (s[i] == '+')
			positive++;

		i++;
	}

	return (n);
}
