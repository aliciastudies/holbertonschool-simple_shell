#include "main.h"

/**
 * print_env - function that print the current environment
 * @array: pointer to array that contains command
 * Return: 0 on sucess
 */
int print_env(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i = i + 1;
	}
	return (0);
}

/**
 * checkbuiltin - function that check whether command passed is builtin command
 * @array: a pointer to array that contains command to be checked
 * @environ: a pointer to array that list environment variable name and value
 * @str: a pointer to user input
 * Return: 0 on success
 */
int checkbuiltin(char **array, char **environ, char *str)
{
	if (array[0] == NULL)
	{
		free(str);
		free(array);
		return (1);
	}
	if (strcmp(array[0], "exit") == 0)
	{
		free(str);
		free(array);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(array[0], "env") == 0)
	{
		print_env(environ);
		free(str);
		free(array);
		return (1);
	}
	return (0);
}
