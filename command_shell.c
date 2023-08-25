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
 * fork_the_child - fork to create child process and execute program
 * @command: a pointer to array that hold command
 * @environ: a pointer to array that list environment variable name and value
 * @str: a pointer to the user input string
 * Return: exit status of the child process
 */

int fork_the_child(char **command, char **environ, char **str, int *status)
{
	int child;
	int wait_status;

	child = fork();

	if (child == 0)
	{
		if (execve(command[0], command, environ) == -1)
		{
			printf("EXECVE FAIL\n");
			free(*str);
			exit(*status);
		}
	}
	else
	{
		waitpid(child, &wait_status, 0);

		if (WIFEXITED(wait_status))
		{
			*status = WEXITSTATUS(wait_status);
		}
		else if (WIFSIGNALED(wait_status))
		{
			*status = WTERMSIG(wait_status);
		}
	}
	return (*status);
}

/**
* line_to_array - a function that splits user input and stores in an array
* @str: a pointer to user input
* @command: a pointer to array that stores tokenised user input
*
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
* executable_cmd - checks if the command is executable and if the user has
* the necessary permissions
* @string: the command to be checked
*
* Return: 1 if executable, else 0
*/
int executable_cmd(char *string)
{
	struct stat st;

	if (stat(string, &st) == 0 && st.st_mode & S_IXUSR)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
