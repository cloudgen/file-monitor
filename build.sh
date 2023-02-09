#!/bin/sh
mkdir -p target
gcc src/main.c \
    src/log-message.c \
    src/make-directory.c \
    src/receiver.c \
    src/receiver-loop.c \
    src/remove-old-log.c \
    src/run-detached.c \
    src/send-cmd.c \
    src/singleton.c \
    -o target/daemon

if [ $? -ne 0 ]; then
    echo "Build failed. Please check the error messages above."
    exit 1
else
    echo "Build successful!"
    echo "  You can run the program by: \"target/daemon\""
    exit 0
fi