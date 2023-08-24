#include "main.h"

/**
 * line_to_array - function that split user input and store in array
 * @str: a pointer to user input
 * @command: a pointer to array that store tokenised user input
 * Return: void
 */

void line_to_array(char *str, char **command)
{
	int i;
	const char *delim;
	char *token;

	i = 0;
	delim = " \t\n\r";
	token = strtok(str, delim);

	while (token != NULL)
	{
		command[i] = token;
		token = strtok(NULL, delim);
		i = i + 1;
	}
	command[i] = NULL;
}

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
