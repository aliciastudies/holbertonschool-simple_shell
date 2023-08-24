#include "main.h"

/**
 * _getenv - function get the value of a environment variable
 * @name: a pointer to name passed in
 *
 * Return: a pointer to value of environment variable on sucess or NULL
 */

char *_getenv(const char *name)
{
	int i = 0;
	int l = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, l) == 0 && environ[i][l] == '=')
		{
			return (&environ[i][l + 1]);
		}
		i = i + 1;
	}
	return (NULL);
}

/**
 * find_executable_in_path - function to search whether command can be
 * located in environment variable PATH
 * @cmd: a pointer to command passed in
 *
 * Return: ful path of environment variable
 */

char *find_executable_in_path(char *cmd)
{
	struct stat st;
	char *path = strdup(_getenv("PATH"));
	char *dir = strtok(path, ":");
	char *filepath = NULL;

	while (dir != NULL)
	{
		filepath = malloc(strlen(dir) + strlen(cmd) + 2);

		if (filepath == NULL)
		{
			perror("Memory allocation error");
			free(path);
			exit(EXIT_FAILURE);
		}

		sprintf(filepath, "%s/%s", dir, cmd);

		if (stat(filepath, &st) == 0 && st.st_mode & S_IXUSR)
		{
			free(path);
			return (filepath);
		}
		free(filepath);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
