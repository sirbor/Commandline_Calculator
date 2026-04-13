#include "ops/programming_ops.h"
#include "utils/utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// CONCEPT: Script functions that can be called by name
static CalculationResult script_sum(double *args, int n) {
    CalculationResult res = {0.0, false, ""};
    for (int i = 0; i < n; i++) {
        res.value += args[i];
    }
    return res;
}

static CalculationResult script_product(double *args, int n) {
    CalculationResult res = {1.0, false, ""};
    for (int i = 0; i < n; i++) {
        res.value *= args[i];
    }
    return res;
}

static CalculationResult script_max(double *args, int n) {
    CalculationResult res = {0.0, false, ""};
    if (n == 0) {
        res.is_error = true;
        strcpy(res.err_message, "No arguments provided.");
        return res;
    }
    res.value = args[0];
    for (int i = 1; i < n; i++) {
        if (args[i] > res.value) res.value = args[i];
    }
    return res;
}

static CalculationResult script_min(double *args, int n) {
    CalculationResult res = {0.0, false, ""};
    if (n == 0) {
        res.is_error = true;
        strcpy(res.err_message, "No arguments provided.");
        return res;
    }
    res.value = args[0];
    for (int i = 1; i < n; i++) {
        if (args[i] < res.value) res.value = args[i];
    }
    return res;
}

static CalculationResult script_avg(double *args, int n) {
    CalculationResult res = script_sum(args, n);
    if (!res.is_error && n > 0) {
        res.value /= n;
    }
    return res;
}

// CONCEPT: Function pointer dispatch table (Day 23)
static ScriptEntry script_table[] = {
    {"sum", script_sum},
    {"product", script_product},
    {"max", script_max},
    {"min", script_min},
    {"avg", script_avg},
    {NULL, NULL}
};

void programming_list_scripts(void) {
    printf("\n");
    printf("    %s╭─ Available Scripts ──────────────╮%s\n", COLOR_SKY, COLOR_RESET);
    for (int i = 0; script_table[i].name != NULL; i++) {
        printf("    %s│%s  %s▸%s %-30s %s│%s\n", 
               COLOR_SKY, COLOR_RESET, COLOR_MINT, COLOR_RESET, 
               script_table[i].name, COLOR_SKY, COLOR_RESET);
    }
    printf("    %s╰───────────────────────────────────╯%s\n", COLOR_SKY, COLOR_RESET);
    printf("    %sUsage:%s programming run <script> <args...>\n\n", STYLE_DIM, COLOR_RESET);
}

// CONCEPT: Function pointer lookup and invocation
void programming_run_script(const char *script_name) {
    for (int i = 0; script_table[i].name != NULL; i++) {
        if (strcmp(script_name, script_table[i].name) == 0) {
            log_info("Script found. Use: programming run <script> <args...>");
            return;
        }
    }
    log_error("Unknown script. Use 'programming list' to see available scripts.");
}

CalculationResult programming_execute(const char *cmd, double *args, int nargs) {
    CalculationResult res = {0.0, true, "Unknown script."};
    
    // CONCEPT: Function pointer lookup
    for (int i = 0; script_table[i].name != NULL; i++) {
        if (strcmp(cmd, script_table[i].name) == 0) {
            // CONCEPT: Calling function through pointer
            return script_table[i].func(args, nargs);
        }
    }
    
    return res;
}
