#include "main.h"
/**
 * get_input - function that read user input
 * @buffer: a pointer to user input
 * @bufsize: variable that holds the size of the allocated buffer
 * @read: a variable to store user input
 */

void get_input(char **buffer, size_t *bufsize, ssize_t *read)
{
	signal(SIGINT, SIG_IGN);
	if (isatty(0) == 1)
	{
		printf("$ ");
	}

	*read = getline(buffer, bufsize, stdin);
	fflush(stdin);

	if (*read == -1)
	{
		free(*buffer);
		exit(EXIT_SUCCESS);
	}
}

/**
 * for_the_chile - fork to create child proecss and execute program
 * @command: pointer to array that hold command
 * @environm: a pointer to array that list environment variable name and value
 * Return: exit status of the child process
 */
int fork_the_child(char **command, char **environ, char **str)
{
	pid_t child;
	char *filepath;
	int status;

	child = fork();

	if (child == -1)
	{
		printf("./hsh: 1: %s: not found", command[0]);
		exit(EXIT_FAILURE);
	}
	else if (child == 0)
	{
		if (strchr(command[0], '/') != NULL)
		{
			if (execve(command[0], command, environ) == -1)
			{
				perror("Error executing command");
				free(command);
				free(*str);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			filepath = find_executable_in_path(command[0]);
			if (filepath != NULL)
			{
				if (execve(filepath, command, environ) == -1)
				{
					perror("Error executing command");
					free(command);
					free(*str);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				printf("./hsh: 1: %s: not found", command[0]);
				free(command);
				return (-1);
			}
		}
	}
	if (child > 0)
	{
		wait(&status);
	}
	return (status);
}

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
