#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// CONCEPT: Preprocessor macros - for versioning and constants
#define MAX_CMD_LEN 1024
#define MAX_ERR_LEN 256
#define VERSION "0.1.0"

// CONCEPT: ANSI Escape sequences for colored output
#define COLOR_GREEN  "\033[0;32m"
#define COLOR_RED    "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_RESET  "\033[0m"

// CONCEPT: Structures - encapsulation of related data
typedef struct {
    double value;
    bool is_error;
    char err_message[MAX_ERR_LEN];
} CalculationResult;

// CONCEPT: Enumerations - readable symbolic constants
typedef enum {
    CMD_BASIC,
    CMD_SCIENTIFIC,
    CMD_STATISTICAL,
    CMD_GRAPHICAL,
    CMD_SOLVER,
    CMD_CALCULUS,
    CMD_MEMORY,
    CMD_PROGRAMMING,
    CMD_CONVERTER,
    CMD_COMPLEX,
    CMD_FINANCIAL,
    CMD_EXTRA,
    CMD_HELP,
    CMD_QUIT,
    CMD_UNKNOWN
} CommandType;

// Forward declarations
void print_banner();
void print_help();

#endif // COMMON_H
