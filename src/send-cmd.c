#include "daemon-info.h"
#include "send-cmd.h"

void send_cmd(const char *command) {
  char cmd[1024];
  struct sockaddr_un name;
  int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

  strcpy(cmd, command);

  if (socket_fd < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  /* Store server address in socket address structure. */
  name.sun_family = AF_UNIX;
  strcpy(name.sun_path, SOCKET_NAME);

  /* Connect to socket. */
  if (connect(socket_fd, (struct sockaddr *) &name, sizeof(struct sockaddr_un)) < 0) {
    perror("connect");
  } else {
    /* Send message to socket. */
    if (write(socket_fd, cmd, strlen(cmd) + 1) < 0) {
      perror("write");
    }
  }
  close(socket_fd);
}