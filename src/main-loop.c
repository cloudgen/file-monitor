#include "main-loop.h"
#include "log-message.h"

void main_loop() {
  while (1) {
    //log_message("Hello");

    /* Release CPU. */
    usleep(1000);
  }
}
