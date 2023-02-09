#ifndef SEND_CMD_H
#define SEND_CMD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MESSAGE "Hello"

void send_cmd(const char *command);

#endif /* SEND_CMD_H */