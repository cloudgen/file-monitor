#ifndef SINGLETON_H
#define SINGLETON_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void check_singleton();
void create_pid_file();

#endif /* SINGLETON_H */
