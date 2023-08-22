#include "main.h"

int main(void)
{
        pid_t child;
        char *command[16], *tok, *lineptr = NULL;
	char *filepath;
	size_t i;
	size_t n;
	ssize_t read;
        int status;

        while (1)
        {
		if (isatty(STDIN_FILENO) == 1)
		{
			printf("$ ");
		}
		read = getline(&lineptr, &n, stdin);
		if (read == -1)
                {
			break;
                }
		tok = strtok(lineptr, " \t\n\r");
                i = 0;
                while (i < 16 && tok != NULL)
                {
                        command[i] = tok;
                        tok = strtok(NULL, " \t\n\r");
                        i = i + 1;
                }
                command[i] = NULL;
                child = fork();
                if (child == 0)
		{
			if (strchr(command[0], '/') != NULL)
			{
				if (execve(command[0], command, environ) == - 1)
				{
					perror("Error executing command");
					exit(127);
				}
			}
			else
			{
				filepath = find_executable_in_path(command[0]);
				if (filepath != NULL)
				{
					if (execve(filepath, command, environ) == -1)
					{
						perror("Error executing");
						exit(127);
					}
				}
				else
				{
					printf("%s: command not found\n", command[0]);
					return (-1);
				}
			}
		}
		if (child > 0)
		{
			wait(&status);
		}
	}
	free(lineptr);
	exit(status);
}
