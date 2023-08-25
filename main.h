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
#include <dirent.h>

extern char **environ;
struct dirent *_readdir(DIR *dp);

/* built_in funcs */
int print_env(char **array);
int checkbuiltin(char **array, char **environ, char *str, int *status);
DIR *_opendir(char *name);
struct dirent *_readdir(DIR *dp);

/* command_shell funcs */
void get_input(char **buffer, size_t *bufsize, ssize_t *read);
int fork_the_child(char **command, char **environ, char **str, int *status);
void line_to_array(char *str, char **command);
int executable_cmd(char *string);

/* find_path funcs */
char *_getenv(char *name);
char *find_executable_in_path(char **cmd, char *prog_av);
void string_into_words(char *string, char **words);
char *get_exe_string(char *path, char *program_av);

#endif
