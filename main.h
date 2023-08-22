#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

typedef struct builtin_cmd
{
        char *name;
        int (*f)(void);
} builtin_cmd_t;

int execute_builtin_cmd(char *tokenised_array);
int print_env();
int exit_shell();
extern char **environ;
char *_getenv(const char *name);
char *find_executable_in_path(char *command);

#endif
