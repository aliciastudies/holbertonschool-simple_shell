#include "main.h"

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
		exit(0);
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
