#include "utils/utils.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// CONCEPT: ANSI Color-coded output for different log levels
void log_info(const char *message) {
    printf("%s[INFO]%s %s\n", COLOR_YELLOW, COLOR_RESET, message);
}

void log_error(const char *message) {
    fprintf(stderr, "%s[ERROR]%s %s\n", COLOR_RED, COLOR_RESET, message);
}

void log_success(const char *message) {
    printf("%s[SUCCESS]%s %s\n", COLOR_GREEN, COLOR_RESET, message);
}

// CONCEPT: String manipulation - removing leading and trailing whitespace
void trim_whitespace(char *str) {
    if (str == NULL || *str == '\0') return;
    
    // CONCEPT: Pointers and string termination
    char *start = str;
    char *end;
    
    // Find first non-whitespace character
    while (isspace((unsigned char)*start)) start++;
    
    if (*start == '\0') {
        // String was all whitespace
        *str = '\0';
        return;
    }
    
    // Find last non-whitespace character
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    
    // Calculate length and move trimmed string to beginning
    size_t len = (size_t)(end - start + 1);
    if (start != str) {
        memmove(str, start, len);
    }
    str[len] = '\0';
}

// CONCEPT: Formatted printing of CalculationResult structure
void print_result(CalculationResult result) {
    if (result.is_error) {
        log_error(result.err_message);
    } else {
        printf("%sResult:%s %.2f\n", COLOR_GREEN, COLOR_RESET, result.value);
    }
}
