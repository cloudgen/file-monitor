#ifndef FILE_MONITOR_H
#define FILE_MONITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <time.h>
#include "remove-old-log.h"

#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME 16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE  (sizeof (struct inotify_event)) /*size of one event*/
#define BUF_LEN     (MAX_EVENTS * (EVENT_SIZE + LEN_NAME)) /*buffer to store the data of events*/

void file_monitor(int fd);

#endif /* FILE_MONITOR_H */
