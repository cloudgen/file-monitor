gcc -o file-monitor \
    src/main.c \
    src/file-monitor.c \
    src/make-directory.c \
    src/run-detached.c \
    src/remove-old-log.c \
    -I./src -Wall
