#include "daemon-info.h"
#include "log-message.h"
#include "remove-old-log.h"

void log_message(const char *msg) {
  char filename[1024];
  char timestamp[100];
  pid_t pid = getpid();
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  strftime(filename, sizeof(filename), LOG_DIR "/daemon-%Y-%m-%d.log", &tm);

  FILE *fp = fopen(filename, "a");
  if (fp == NULL) {
    perror("Failed to open log file");
    return;
  }
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm);
  fprintf(fp, "%s %s #%d :] %s\n",timestamp, APP_NAME, pid, msg);
  fclose(fp);
  remove_old_logs(LOG_DIR);
}