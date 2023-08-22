#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

char *user_getline(void)
{
	char *buf;
	size_t bufsize;
	ssize_t getline_return;

	buf = NULL;
	bufsize = 0;

	getline_return = getline(&buf, &bufsize, stdin);
	if ((getline_return = EOF))
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

int main(void)
{
        pid_t child;
        char *command[16], *tok, *lineptr = NULL;
        size_t i;
	char *read;
        int status;

        while (1)
        {
		if (isatty(STDIN_FILENO) == 1)
		{
			printf("$ ");
		}
		read = user_getline();
		if (read == NULL)
                {
                        return (0);
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
                        if (execve(command[0], command, NULL) == -1)
                        {
                                exit(EXIT_FAILURE);
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
