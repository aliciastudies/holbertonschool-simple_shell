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
 * @status: a pointer to a variable that stores the exit status of the shell
 * Return: 0 on success
 */
int checkbuiltin(char **array, char **environ, char *str, int *status)
{
	if (array[0] == NULL)
	{
		free(str);
		return (1);
	}
	if (strcmp(array[0], "exit") == 0)
	{
		free(str);
		exit(*status);
	}
	else if (strcmp(array[0], "env") == 0)
	{
		print_env(environ);
		free(str);
		return (1);
	}
	return (0);
}

/**
* _opendir - opens a directory
* @name: directory name
*
* Return: pointer to a directory stream
*/
DIR *_opendir(char *name)
{
	DIR *dp;

	dp = opendir(name);

	if (dp == NULL)
	{
		perror("open directory");
		return (NULL);
	}
	return (dp);
}

/**
* _readdir - returns a pointer to a structure representing the next directory
* entry in the directory stream
* @dp: pointer to a directory stream
*
* Return: pointer to a directory entry struct
*/
struct dirent *_readdir(DIR *dp)
{
	struct dirent *ep;

	ep = readdir(dp);

	if (ep == NULL)
	{
		return (NULL);
	}
	return (ep);
}
