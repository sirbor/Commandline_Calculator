#include "utils/signals.h"
#include "cleanup.h"
#include "utils/utils.h"
#include "common.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_sigint(int sig) {
    (void)sig;
    printf("\n\n");
    printf("  %s╭────────────────────────────────╮%s\n", COLOR_CORAL, COLOR_RESET);
    printf("  %s│%s  %s%s%s Interrupt received (Ctrl+C)   %s│%s\n", 
           COLOR_CORAL, COLOR_RESET, COLOR_GOLD, SYM_WARN, COLOR_RESET, COLOR_CORAL, COLOR_RESET);
    printf("  %s╰────────────────────────────────╯%s\n", COLOR_CORAL, COLOR_RESET);
    cleanup_calculator();
    exit(0);
}

void setup_signal_handlers(void) {
    signal(SIGINT, handle_sigint);
}
