#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/inotify.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include "file-monitor.h"
#include "run-detached.h"
#include "make-directory.h"
#include "remove-old-log.h"
int main(int argc, char** argv) {
    int fd;

    if (make_directory("/data/log/file-monitor") != 0) {
        printf("Error creating directory\n");
        return 1;
    }
    run_detached();

    /* Initialize Inotify*/
    fd = inotify_init();
    if (fd < 0) {
        perror("Couldn't initialize inotify");
        exit(EXIT_FAILURE);
    }
    file_monitor(fd);
    return 0;
}
 
