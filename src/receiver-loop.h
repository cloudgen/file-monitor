#ifndef RECEIVER_LOOP_H
#define RECEIVER_LOOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void receiver_loop(int socket_fd);

#endif /* RECEIVER_LOOP_H */
