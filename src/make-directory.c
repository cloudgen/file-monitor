#include "make-directory.h"

int make_directory(const char *path) {
  char dir[1024];
  strcpy(dir, path);
  int len = strlen(dir);
  if (dir[len - 1] == '/') {
    dir[len - 1] = 0;
  }
  char *p = dir + 1;
  while (*p) {
    if (*p == '/') {
      *p = 0;
      if (mkdir(dir, 0700) && errno != EEXIST) {
        return -1;
      }
      *p = '/';
    }
    p++;
  }
  if (mkdir(dir, 0700) && errno != EEXIST) {
    return -1;
  }
  return 0;
}