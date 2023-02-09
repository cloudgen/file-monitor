#include <stdio.h>
#include <string.h>
#include "singleton.h"
#include "daemon-info.h"
#include "log-message.h"
#include "receiver.h"
#include "make-directory.h"
#include "remove-old-log.h"
#include "run-detached.h"
#include "send-cmd.h"

void handle_exit(int sig) {
  unlink(SOCKET_NAME);
  unlink(PID_FILE);
  log_message("Terminated");
  exit(0);
}

int main(int argc, char *argv[]) {

  if (make_directory(LOG_DIR) != 0) {
    fprintf(stderr, "Error creating directory\n");
    return 1;
  }

  if (argc > 1 && strcmp(argv[1], "-d") == 0) {
    check_singleton();
    printf("Starting Daemon mode\n");
    run_detached();
    signal(SIGINT, handle_exit);
    signal(SIGTERM, handle_exit);
    log_message("Daemon Started");
    create_pid_file();
    receiver(); 
    log_message("Daemon Ended Unexpected");
  } else {
    send_cmd(argv[1]);
  }
  return 0;
}
