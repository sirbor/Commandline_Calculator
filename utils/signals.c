#include "utils/signals.h"
#include "cleanup.h"
#include "utils/utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// CONCEPT: Signal handler function
void handle_sigint(int sig) {
    (void)sig; // CONCEPT: Void cast to ignore unused parameter
    printf("\n");
    log_info("Caught interrupt signal (Ctrl+C). Cleaning up...");
    cleanup_calculator();
    exit(0);
}

void setup_signal_handlers() {
    // CONCEPT: signal() to register a handler
    signal(SIGINT, handle_sigint);
}
