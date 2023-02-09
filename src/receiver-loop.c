#include "receiver-loop.h"
#include "log-message.h"

void receiver_loop(int socket_fd) {
  char buffer[100];
  int connection_fd;

  log_message("Waiting for incomming message.");
  while (1) {
    char s[] = "Received message: ";
    /* Accept connection. */
    connection_fd = accept(socket_fd, NULL, NULL);
    if (connection_fd < 0) {
      perror("accept");
      log_message("Connection Error");
      exit(EXIT_FAILURE);
    }

    /* Read message from socket. */
    if (read(connection_fd, buffer, sizeof(buffer)) < 0) {
      perror("read");
      log_message("Unable to read");
      exit(EXIT_FAILURE);
    }
    strcat(s, buffer);
    log_message(s);

    if (0 == strcmp(buffer, "exit")){
      log_message("Terminated");
      exit(EXIT_SUCCESS);
    }
    /* Close connection. */
    close(connection_fd);
    
    /* Release CPU. */
    usleep(1);
  }
}
