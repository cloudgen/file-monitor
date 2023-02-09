#include "receiver.h"
#include "receiver-loop.h"
#include "daemon-info.h"
#include "log-message.h"

void receiver() {
    int socket_fd;
    struct sockaddr_un name;
    char buffer[100];

    /* Create socket. */
    unlink(SOCKET_NAME);
    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket");
        log_message("Socket Error!");
        exit(EXIT_FAILURE);
    }

    /* Store socket address in socket address structure. */
    name.sun_family = AF_UNIX;
    strcpy(name.sun_path, SOCKET_NAME);

    /* Bind socket to socket address. */
    if (bind(socket_fd, (struct sockaddr *) &name, sizeof(struct sockaddr_un)) < 0) {
        perror("bind");
        log_message("Binding Error!");
        exit(EXIT_FAILURE);
    }

    /* Listen to socket. */
    if (listen(socket_fd, 5) < 0) {
        perror("listen");
        log_message("Listening Error!");
        exit(EXIT_FAILURE);
    }

    receiver_loop(socket_fd);
}
