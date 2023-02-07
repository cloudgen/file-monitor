#ifndef REMOVE_OLD_LOG_H
#define REMOVE_OLD_LOG_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
void remove_old_logs(const char *dir);

#endif // REMOVE_OLD_LOG_H
