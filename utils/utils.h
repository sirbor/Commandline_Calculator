#ifndef UTILS_H
#define UTILS_H

#include "common.h"

// CONCEPT: Format specifiers and escape sequences (Day 3)
void log_info(const char *message);
void log_error(const char *message);
void log_success(const char *message);

// CONCEPT: Robust string handling
void trim_whitespace(char *str);

// CONCEPT: Variadic functions (Day 25 concept, but let's stick to basics for now)
void print_result(CalculationResult result);

#endif // UTILS_H
