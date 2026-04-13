#include "utils/utils.h"
#include "ops/history_ops.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void log_info(const char *message) {
    printf("\n    %s○%s %s%s%s\n", COLOR_SKY, COLOR_RESET, STYLE_DIM, message, COLOR_RESET);
}

void log_error(const char *message) {
    fprintf(stderr, "\n    %s╭─%s %sError%s\n", COLOR_CORAL, COLOR_RESET, COLOR_CORAL, COLOR_RESET);
    fprintf(stderr, "    %s│%s %s%s%s\n", COLOR_CORAL, COLOR_RESET, STYLE_DIM, message, COLOR_RESET);
    fprintf(stderr, "    %s╰─────────────────────────────────%s\n\n", COLOR_CORAL, COLOR_RESET);
}

void log_success(const char *message) {
    printf("\n    %s%s%s %s%s%s\n", COLOR_MINT, SYM_CHECK, COLOR_RESET, COLOR_MINT, message, COLOR_RESET);
}

void log_warning(const char *message) {
    printf("\n    %s%s%s %s%s%s\n", COLOR_GOLD, SYM_WARN, COLOR_RESET, COLOR_GOLD, message, COLOR_RESET);
}

void trim_whitespace(char *str) {
    if (str == NULL || *str == '\0') return;
    
    char *start = str;
    char *end;
    
    while (isspace((unsigned char)*start)) start++;
    
    if (*start == '\0') {
        *str = '\0';
        return;
    }
    
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    
    size_t len = (size_t)(end - start + 1);
    if (start != str) {
        memmove(str, start, len);
    }
    str[len] = '\0';
}

void print_result(CalculationResult result) {
    if (result.is_error) {
        log_error(result.err_message);
    } else {
        history_add(result.value);
        printf("\n");
        
        // Format number nicely
        char num_str[32];
        if (fabs(result.value) < 1e-10 && result.value != 0) {
            snprintf(num_str, sizeof(num_str), "%.6e", result.value);
        } else if (fabs(result.value) >= 1e10) {
            snprintf(num_str, sizeof(num_str), "%.6e", result.value);
        } else if (result.value == (long long)result.value && fabs(result.value) < 1e15) {
            snprintf(num_str, sizeof(num_str), "%lld", (long long)result.value);
        } else {
            snprintf(num_str, sizeof(num_str), "%.6g", result.value);
        }
        
        int num_len = (int)strlen(num_str);
        int box_width = (num_len < 10) ? 16 : num_len + 6;
        int padding = box_width - num_len - 4;
        
        printf("    %s╭", COLOR_TEAL);
        for (int i = 0; i < box_width; i++) printf("─");
        printf("╮%s\n", COLOR_RESET);
        
        printf("    %s│%s  %s%s%s  %s%s%s", 
               COLOR_TEAL, COLOR_RESET,
               COLOR_MINT, SYM_APPROX, COLOR_RESET,
               COLOR_GOLD, num_str, COLOR_RESET);
        for (int i = 0; i < padding; i++) printf(" ");
        printf("%s│%s\n", COLOR_TEAL, COLOR_RESET);
        
        printf("    %s╰", COLOR_TEAL);
        for (int i = 0; i < box_width; i++) printf("─");
        printf("╯%s\n\n", COLOR_RESET);
    }
}
