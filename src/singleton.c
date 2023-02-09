#include "singleton.h"
#include "daemon-info.h"
#include "log-message.h"

void check_singleton() {
  int pid_file = open(PID_FILE, O_RDONLY);
  if (pid_file >= 0) {
    int prev_pid;
    if (read(pid_file, &prev_pid, sizeof(int)) == sizeof(int)) {
      if (kill(prev_pid, 0) == 0) {
        fprintf(stderr, "Another instance is already running with PID %d\n", prev_pid);
        exit(1);
      }
    }
    close(pid_file);
    unlink(PID_FILE);
  }
}

void create_pid_file() {
  int pid_file = open(PID_FILE, O_CREAT | O_EXCL | O_WRONLY, 0644);
  if (pid_file < 0) {
    perror("Failed to create PID file");
    log_message("Failed to create PID file");
    exit(1);
  }

  int pid = getpid();
  if (write(pid_file, &pid, sizeof(int)) != sizeof(int)) {
    perror("Failed to write PID to file");
    log_message("Failed to write PID to file");
    unlink(PID_FILE);
    exit(1);
  }
  close(pid_file);

}