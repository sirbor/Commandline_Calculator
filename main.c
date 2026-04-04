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
    printf("\n%s=== CALCULATOR HELP ===%s\n", COLOR_GREEN, COLOR_RESET);
    
    printf("\n%s[BASIC]%s Arithmetic operations\n", COLOR_YELLOW, COLOR_RESET);
    printf("  basic add <a> <b>        Add two numbers\n");
    printf("  basic sub <a> <b>        Subtract b from a\n");
    printf("  basic mul <a> <b>        Multiply two numbers\n");
    printf("  basic div <a> <b>        Divide a by b\n");
    printf("  Example: basic add 5 3 → 8.00\n");
    
    printf("\n%s[SCIENTIFIC]%s Trig and factorial\n", COLOR_YELLOW, COLOR_RESET);
    printf("  scientific sin <x> [deg] Sine (radians or degrees)\n");
    printf("  scientific cos <x> [deg] Cosine (radians or degrees)\n");
    printf("  scientific fact <n>      Factorial of n\n");
    printf("  Example: scientific sin 30 deg → 0.50\n");
    
    printf("\n%s[STATISTICAL]%s Data analysis\n", COLOR_YELLOW, COLOR_RESET);
    printf("  statistical mean <values...>   Calculate mean\n");
    printf("  statistical stddev <values...> Calculate std deviation\n");
    printf("  Example: statistical mean 10 20 30 → 20.00\n");
    
    printf("\n%s[GRAPHICAL]%s ASCII plotting\n", COLOR_YELLOW, COLOR_RESET);
    printf("  graphical plot <expr>    Plot function (sin(x), cos(x), x, x^2)\n");
    printf("  Example: graphical plot sin(x)\n");
    
    printf("\n%s[CALCULUS]%s Numerical integration\n", COLOR_YELLOW, COLOR_RESET);
    printf("  calculus integral <expr> <a> <b> [n]\n");
    printf("  Example: calculus integral sin(x) 0 3.14 → 2.00\n");
    
    printf("\n%s[SOLVER]%s Matrix operations\n", COLOR_YELLOW, COLOR_RESET);
    printf("  solver matrix_det <a> <b> <c> <d>  2x2 determinant\n");
    printf("  Example: solver matrix_det 1 2 3 4 → -2.00\n");
    
    printf("\n%s[MEMORY]%s Store and recall values\n", COLOR_YELLOW, COLOR_RESET);
    printf("  memory store <value>     Store a value\n");
    printf("  memory recall            Recall last stored value\n");
    printf("  Example: memory store 42\n");
    
    printf("\n%s[COMPLEX]%s Complex number arithmetic\n", COLOR_YELLOW, COLOR_RESET);
    printf("  complex add <a+bi> <c+di>  Add complex numbers\n");
    printf("  complex sub <a+bi> <c+di>  Subtract complex numbers\n");
    printf("  complex mul <a+bi> <c+di>  Multiply complex numbers\n");
    printf("  complex div <a+bi> <c+di>  Divide complex numbers\n");
    printf("  complex mag <a+bi>         Magnitude |z|\n");
    printf("  Example: complex add 3+4i 1+2i → 4.00+6.00i\n");
    
    printf("\n%s[FINANCIAL]%s Financial calculations\n", COLOR_YELLOW, COLOR_RESET);
    printf("  financial npv <rate> <cashflows...>  Net Present Value\n");
    printf("  financial compound <P> <r> <n>       Compound interest\n");
    printf("  Example: financial npv 0.1 -1000 500 600\n");
    printf("  Example: financial compound 1000 0.05 10 → 1628.89\n");
    
    printf("\n%s[CONVERTER]%s Unit conversions & bit ops\n", COLOR_YELLOW, COLOR_RESET);
    printf("  converter length <val> <from> <to>  Length conversion\n");
    printf("    Units: m, cm, mm, km, in, ft, yd, mi\n");
    printf("  converter temp <val> <from> <to>    Temperature conversion\n");
    printf("    Units: C, F, K\n");
    printf("  converter to_binary <n>             Show decimal value\n");
    printf("  converter check_bit <n> <bit>       Check bit at position\n");
    printf("  Example: converter length 100 cm m → 1.00\n");
    printf("  Example: converter temp 100 C F → 212.00\n");
    
    printf("\n%s[PROGRAMMING]%s Script execution\n", COLOR_YELLOW, COLOR_RESET);
    printf("  programming list                    List available scripts\n");
    printf("  programming run <script> <args...>  Run a script\n");
    printf("    Scripts: sum, product, max, min, avg\n");
    printf("  Example: programming run sum 1 2 3 4 5 → 15.00\n");
    
    printf("\n%s[EXTRA]%s File operations\n", COLOR_YELLOW, COLOR_RESET);
    printf("  extra save <value> <file>  Save result to file\n");
    printf("  extra load <file>          Load and average values from file\n");
    printf("  Example: extra save 42 result.txt\n");
    
    printf("\n%s[SYSTEM]%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("  help                       Show this help\n");
    printf("  quit / exit                Exit calculator\n");
    printf("\n");
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
