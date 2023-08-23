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

extern char **environ;

void get_input(char **buffer, size_t *bufsize, ssize_t *read);
int fork_the_child(char **command, char **environ, char **str);
void line_to_array(char *str, char **command);
int execute_builtin_cmd(char *tokenised_array);

int print_env(char **array);
int checkbuiltin(char **array, char **environ, char *str);

char *_getenv(const char *name);
char *find_executable_in_path(char *command);

#endif
