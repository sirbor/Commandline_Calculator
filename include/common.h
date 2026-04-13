#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// CONCEPT: Preprocessor macros - for versioning and constants
#define MAX_CMD_LEN 1024
#define MAX_ERR_LEN 256
#define VERSION "2.0.0"

// CONCEPT: ANSI Escape sequences for colored output
// Regular colors
#define COLOR_BLACK   "\033[0;30m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[0;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN    "\033[0;36m"
#define COLOR_WHITE   "\033[0;37m"

// Bold colors
#define COLOR_BOLD_RED     "\033[1;31m"
#define COLOR_BOLD_GREEN   "\033[1;32m"
#define COLOR_BOLD_YELLOW  "\033[1;33m"
#define COLOR_BOLD_BLUE    "\033[1;34m"
#define COLOR_BOLD_MAGENTA "\033[1;35m"
#define COLOR_BOLD_CYAN    "\033[1;36m"
#define COLOR_BOLD_WHITE   "\033[1;37m"

// 256-color mode for modern terminals (gradient effects)
#define COLOR_ORANGE      "\033[38;5;208m"
#define COLOR_PINK        "\033[38;5;213m"
#define COLOR_TEAL        "\033[38;5;45m"
#define COLOR_LIME        "\033[38;5;118m"
#define COLOR_PURPLE      "\033[38;5;141m"
#define COLOR_CORAL       "\033[38;5;209m"
#define COLOR_SKY         "\033[38;5;117m"
#define COLOR_GOLD        "\033[38;5;220m"
#define COLOR_MINT        "\033[38;5;121m"
#define COLOR_LAVENDER    "\033[38;5;183m"

// Gradient colors for banner
#define GRAD_1   "\033[38;5;51m"
#define GRAD_2   "\033[38;5;50m"
#define GRAD_3   "\033[38;5;49m"
#define GRAD_4   "\033[38;5;48m"
#define GRAD_5   "\033[38;5;47m"
#define GRAD_6   "\033[38;5;46m"

// Background colors
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"

// Text styles
#define STYLE_BOLD      "\033[1m"
#define STYLE_DIM       "\033[2m"
#define STYLE_ITALIC    "\033[3m"
#define STYLE_UNDERLINE "\033[4m"
#define STYLE_BLINK     "\033[5m"
#define STYLE_REVERSE   "\033[7m"
#define COLOR_RESET     "\033[0m"

// Modern rounded box drawing characters (UTF-8)
#define BOX_TL "╭"
#define BOX_TR "╮"
#define BOX_BL "╰"
#define BOX_BR "╯"
#define BOX_H  "─"
#define BOX_V  "│"
#define BOX_LT "├"
#define BOX_RT "┤"

// Classic double-line box (for headers)
#define DBOX_TL "╔"
#define DBOX_TR "╗"
#define DBOX_BL "╚"
#define DBOX_BR "╝"
#define DBOX_H  "═"
#define DBOX_V  "║"
#define DBOX_LT "╠"
#define DBOX_RT "╣"

// Modern symbols
#define SYM_CHECK    "✔"
#define SYM_CROSS    "✘"
#define SYM_ARROW    "→"
#define SYM_ARROW_R  "▸"
#define SYM_BULLET   "●"
#define SYM_CIRCLE   "○"
#define SYM_STAR     "★"
#define SYM_SPARK    "✦"
#define SYM_DIAMOND  "◆"
#define SYM_CALC     "⌘"
#define SYM_GRAPH    "◈"
#define SYM_MATH     "∑"
#define SYM_PI       "π"
#define SYM_LAMBDA   "λ"
#define SYM_DELTA    "Δ"
#define SYM_INFO     "●"
#define SYM_WARN     "⚠"
#define SYM_ERROR    "✖"
#define SYM_PROMPT   "❯"
#define SYM_WAVE     "∿"
#define SYM_INTEGRAL "∫"
#define SYM_SQRT     "√"
#define SYM_INFINITY "∞"
#define SYM_APPROX   "≈"

// CONCEPT: Variadic macros (Day 25)
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) ((void)0)
#endif

// CONCEPT: Structures - encapsulation of related data
typedef struct {
    double value;
    bool is_error;
    char err_message[MAX_ERR_LEN];
} CalculationResult;

// CONCEPT: Complex number structure (Day 15)
typedef struct {
    double real;
    double imag;
} Complex;

// CONCEPT: Union - different types sharing same memory (Day 17)
typedef union {
    int i;
    double d;
    char c;
    Complex z;
} DataUnion;

// CONCEPT: Tagged union pattern for type-safe unions
typedef enum {
    DATA_INT,
    DATA_DOUBLE,
    DATA_CHAR,
    DATA_COMPLEX
} DataType;

typedef struct {
    DataType type;
    DataUnion data;
} TaggedData;

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
    CMD_HISTORY,
    CMD_HELP,
    CMD_QUIT,
    CMD_UNKNOWN
} CommandType;

// Forward declarations
void print_banner(void);
void print_help(void);

#endif // COMMON_H
