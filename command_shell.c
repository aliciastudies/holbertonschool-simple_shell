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
 * handle_error - handles error codes
 * @command: a pointer to array that holds command
 * @str: a pointer to the user input string
 * @error: a pointer to array that holds the error emssage displayed
 * Return: void
 */

void handle_error(char **command, char **str, char *error)
{
	perror(error);
	free(command);
	free(*str);
}

/**
 * execute_command - executes a command
 * @command: a pointer to array that holds the command
 * @environ: a pointer to array that lists environ vars to be executed
 * @str: a pointer to the user input string
 * @fpath: a pointer to path fo the executable file to be executed
 * Return: void
 */
void execute_command(char **command, char **environ, char **str, char *fpath)
{

	if (execve(fpath, command, environ) == -1)
	{
		handle_error(command, str, "Error executing command");
		exit(EXIT_FAILURE);
	}
}

/**
 * fork_the_child - fork to create child process and execute program
 * @command: a pointer to array that hold command
 * @environ: a pointer to array that list environment variable name and value
 * @str: a pointer to the user input string
 * Return: exit status of the child process
 */

int fork_the_child(char **command, char **environ, char **str)
{
	pid_t child;
	char *fpath;
	int status;

	fpath = find_executable_in_path(command[0]);
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
			execute_command(command, environ, str, command[0]);
		}
		else
		{
			if (fpath != NULL)
			{
				execute_command(command, environ, str, fpath);
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
