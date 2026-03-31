#include "common.h"
#include "command_handler.h"
#include "utils/utils.h"
#include "utils/signals.h"
#include "initialization.h"
#include "cleanup.h"
#include <stdio.h>
#include <string.h>

// CONCEPT: Function definition and modular design
void print_banner() {
    printf("%s", COLOR_GREEN);
    printf("==========================================\n");
    printf("  Advanced CLI Calculator - v%s  \n", VERSION);
    printf("  30-Day C Programming Mastery Project  \n");
    printf("==========================================\n");
    printf("%s", COLOR_RESET);
}

void print_help() {
    printf("\nAvailable Command Categories:\n");
    printf(" - basic, scientific, statistical, graphical, solver\n");
    printf(" - calculus, memory, programming, converter, complex\n");
    printf(" - financial, extra, help, quit\n");
    printf("\nExample: basic add 5 3\n");
}

// CONCEPT: Main entry point with CLI loop
int main() {
    char input[MAX_CMD_LEN];
    
    setup_signal_handlers();
    initialize_calculator();
    print_banner();
    printf("Type 'help' for a list of commands or 'quit' to exit.\n");

    while (true) {
        printf("\ncalculator> ");
        
        // CONCEPT: Safe input with fgets (Day 3 concept but useful now)
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // CONCEPT: String manipulation - remove trailing newline
        input[strcspn(input, "\n")] = 0;

        // CONCEPT: Control flow - early exit
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            print_help();
            continue;
        } else if (strlen(input) == 0) {
            continue;
        }

        // CONCEPT: Modular command handling
        handle_command(input);
    }

    cleanup_calculator();
    return 0;
}
