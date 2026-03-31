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
    if (str == NULL) return;
    
    // CONCEPT: Pointers and string termination
    char *end;
    
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) return; // All spaces
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator
    *(end + 1) = 0;
}

// CONCEPT: Formatted printing of CalculationResult structure
void print_result(CalculationResult result) {
    if (result.is_error) {
        log_error(result.err_message);
    } else {
        printf("%sResult:%s %.2f\n", COLOR_GREEN, COLOR_RESET, result.value);
    }
}
