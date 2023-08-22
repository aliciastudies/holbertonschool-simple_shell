#include "main.h"

char *_getenv(const char *name)
{
  int i = 0;
  int len = strlen(name);

  while(environ[i] != NULL)
    {
      if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
      {
        return(&environ[i][len + 1]);
      }
      i = i + 1;
    }
  return (NULL);
}

struct stat st;

char *find_executable_in_path(char *command)
{
  char *path = strdup(_getenv("PATH"));
  char *directory = strtok(path, ":");

  while (directory != NULL)
    {
      char *filepath = malloc(strlen(directory) + strlen(command) + 2);
      sprintf(filepath, "%s/%s", directory, command);

      if (stat(filepath, &st) == 0 && st.st_mode & S_IXUSR)
      {
        return (filepath);
      }
      free(filepath);
      directory = strtok(NULL, ":");
    }
  free(path);
  return (NULL);
}
