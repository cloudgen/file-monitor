#include "remove-old-log.h"

void remove_old_logs(const char *dir) {
  DIR *d = opendir(dir);
  if (d == NULL) {
    printf("Error opening directory: %s\n", dir);
    return;
  }
  time_t now = time(NULL);
  struct dirent *entry;
  while ((entry = readdir(d)) != NULL) {
    if (entry->d_type == DT_REG) {
      char path[1024];
      sprintf(path, "%s/%s", dir, entry->d_name);

      struct stat statbuf;
      if (stat(path, &statbuf) == 0) {
        double age = difftime(now, statbuf.st_mtime);
        if (age > 60 * 60 * 24 * 7) {
          if (remove(path) != 0) {
            printf("Error removing file: %s\n", path);
          }
        }
      }
    }
  }
  closedir(d);
}
