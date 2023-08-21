#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
        pid_t child;
        char *command[16], *tok, *lineptr = NULL;
        size_t i;
        size_t n;
        int status;

        while (1)
        {
                printf("$ ");
                if (getline(&lineptr, &n, stdin) == -1)
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
                        if (execve(command[0], command, NULL))
                        {
                                perror("execve");
                                exit(EXIT_FAILURE);
                        }
                }
                if (child > 0)
                {
                        wait(&status);
                }
        }
        printf("\n");
        free(lineptr);
        exit(status);
}

