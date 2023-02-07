#include "file-monitor.h"

void file_monitor(int fd) {
    int i, length;
    char buffer[BUF_LEN];
    pid_t pid = getpid();
    char timestamp[100];
    /* add watch to starting directory */
    int wd = inotify_add_watch(fd, "/data/ipfs-smb", IN_MODIFY | IN_CREATE | IN_DELETE);
    if (wd == -1) {
        perror("Couldn't add watch to /data/ipfs-smb");
        exit(EXIT_FAILURE);
    }

    /* do it forever*/
    while(1){
        i = 0;
        length = read(fd, buffer, BUF_LEN);  

        if (length < 0) {
            perror("read");
        }  

        /* check for events */
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if (event->len) {
                char filename[100];
                time_t current_time;
                struct tm *time_info;
                time(&current_time);
                time_info = localtime(&current_time);
                strftime(filename, sizeof(filename), "/data/log/file-monitor/fmon-%Y-%m-%d.log", time_info);
                strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
                FILE *file = fopen(filename, "a");
                if (file == NULL) {
                    printf("Error opening file: %s\n", filename);
                    exit(1);
                }
                if (event->mask & IN_CREATE) {
                    if (event->mask & IN_ISDIR) {
                        fprintf(file, "%s FMon(2.7) #%d :] The directory %s was created.\n",timestamp, pid, event->name);
                    }
                    else {
                        fprintf(file, "%s FMon(2.7) #%d :] The file %s was created.\n",timestamp, pid, event->name);
                    }
                }
                else if (event->mask & IN_MODIFY) {
                    fprintf(file, "%s FMon(2.7) #%d :] The file %s was modified.\n",timestamp, pid, event->name);
                }
                else if (event->mask & IN_DELETE) {
                    if (event->mask & IN_ISDIR) {
                        fprintf(file, "%s FMon(2.7) #%d :] The directory %s was deleted.\n",timestamp, pid, event->name);
                    }
                    else {
                        fprintf(file, "%s FMon(2.7) #%d :] The file %s was deleted.\n",timestamp, pid, event->name);
                    }
                }
                fclose(file);
            }
            i += EVENT_SIZE + event->len;
        }
        remove_old_logs("/data/log/file-monitor");
        sleep(1);
    }
}
