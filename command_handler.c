#include "command_handler.h"
#include "ops/basic_ops.h"
#include "ops/scientific_ops.h"
#include "ops/memory_ops.h"
#include "ops/statistical_ops.h"
#include "ops/converter_ops.h"
#include "ops/graphical_ops.h"
#include "ops/calculus_ops.h"
#include "ops/solver_ops.h"
#include "ops/extra_ops.h"
#include "ops/complex_ops.h"
#include "ops/financial_ops.h"
#include "ops/programming_ops.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    CommandType type;
    CommandHandlerFunc handler;
} CommandEntry;

void handle_basic(const char *args);
void handle_scientific(const char *args);
void handle_memory(const char *args);
void handle_statistical(const char *args);
void handle_converter(const char *args);
void handle_graphical(const char *args);
void handle_calculus(const char *args);
void handle_solver(const char *args);
void handle_extra(const char *args);
void handle_complex(const char *args);
void handle_financial(const char *args);
void handle_programming(const char *args);

static CommandEntry command_table[] = {
    {"basic", CMD_BASIC, handle_basic},
    {"scientific", CMD_SCIENTIFIC, handle_scientific},
    {"memory", CMD_MEMORY, handle_memory},
    {"statistical", CMD_STATISTICAL, handle_statistical},
    {"converter", CMD_CONVERTER, handle_converter},
    {"graphical", CMD_GRAPHICAL, handle_graphical},
    {"calculus", CMD_CALCULUS, handle_calculus},
    {"solver", CMD_SOLVER, handle_solver},
    {"extra", CMD_EXTRA, handle_extra},
    {"complex", CMD_COMPLEX, handle_complex},
    {"financial", CMD_FINANCIAL, handle_financial},
    {"programming", CMD_PROGRAMMING, handle_programming},
    {"help", CMD_HELP, NULL},
    {"quit", CMD_QUIT, NULL},
    {NULL, CMD_UNKNOWN, NULL}
};

void handle_command(const char *command_str) {
    char cmd_line[MAX_CMD_LEN];
    strncpy(cmd_line, command_str, MAX_CMD_LEN - 1);
    cmd_line[MAX_CMD_LEN - 1] = '\0';  // Ensure null-termination
    char *cmd_name = strtok(cmd_line, " ");
    if (!cmd_name) return;
    char *args = strtok(NULL, "");
    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strcmp(cmd_name, command_table[i].name) == 0) {
            if (command_table[i].handler != NULL) {
                command_table[i].handler(args);
                return;
            } else if (command_table[i].type == CMD_HELP) {
                print_help();
                return;
            }
        }
    }
    log_error("Unknown command. Type 'help'.");
}

void handle_basic(const char *args) {
    if (!args) { log_error("Usage: basic <op> <v1> <v2>"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " "), *v1s = strtok(NULL, " "), *v2s = strtok(NULL, " ");
    if (!op || !v1s || !v2s) { log_error("Usage: basic <op> <v1> <v2>"); return; }
    double v1, v2;
    if (sscanf(v1s, "%lf", &v1) != 1 || sscanf(v2s, "%lf", &v2) != 1) {
        log_error("Invalid number format"); return;
    }
    CalculationResult res;
    if (strcmp(op, "add") == 0) res = basic_add(v1, v2);
    else if (strcmp(op, "sub") == 0) res = basic_sub(v1, v2);
    else if (strcmp(op, "mul") == 0) res = basic_mul(v1, v2);
    else if (strcmp(op, "div") == 0) res = basic_div(v1, v2);
    else return;
    print_result(res);
}

void handle_scientific(const char *args) {
    if (!args) { log_error("Usage: scientific <op> <value> [deg]"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " "), *v1s = strtok(NULL, " "), *v2s = strtok(NULL, " ");
    if (!op || !v1s) { log_error("Usage: scientific <op> <value> [deg]"); return; }
    double v1;
    if (sscanf(v1s, "%lf", &v1) != 1) { log_error("Invalid number format"); return; }
    bool is_deg = (v2s && strcmp(v2s, "deg") == 0);
    CalculationResult res;
    if (strcmp(op, "sin") == 0) res = scientific_sin(v1, is_deg);
    else if (strcmp(op, "cos") == 0) res = scientific_cos(v1, is_deg);
    else if (strcmp(op, "fact") == 0) res = scientific_factorial((int)v1);
    else return;
    print_result(res);
}

void handle_memory(const char *args) {
    if (!args) { log_error("Usage: memory <store|recall> [value]"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: memory <store|recall> [value]"); return; }
    if (strcmp(op, "store") == 0) {
        char *vs = strtok(NULL, " ");
        if (!vs) { log_error("Usage: memory store <value>"); return; }
        double v;
        if (sscanf(vs, "%lf", &v) != 1) { log_error("Invalid number format"); return; }
        memory_store(v);
        log_success("Stored.");
    } else if (strcmp(op, "recall") == 0) {
        print_result(memory_recall());
    } else {
        log_error("Unknown memory operation. Use: store, recall");
    }
}

void handle_statistical(const char *args) {
    if (!args) { log_error("Usage: statistical <mean|stddev> <values...>"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: statistical <mean|stddev> <values...>"); return; }
    int cap = 10, count = 0;
    double *data = malloc(cap * sizeof(double));
    if (!data) { log_error("Memory allocation failed"); return; }
    char *t = strtok(NULL, " ");
    while (t) {
        if (count >= cap) {
            cap *= 2;
            double *new_data = realloc(data, cap * sizeof(double));
            if (!new_data) { free(data); log_error("Memory allocation failed"); return; }
            data = new_data;
        }
        if (sscanf(t, "%lf", &data[count]) == 1) count++;
        t = strtok(NULL, " ");
    }
    if (count == 0) { free(data); log_error("No valid numbers provided"); return; }
    CalculationResult res;
    if (strcmp(op, "mean") == 0) res = statistical_mean(data, count);
    else if (strcmp(op, "stddev") == 0) res = statistical_stddev(data, count);
    else { free(data); return; }
    print_result(res); free(data);
}

void handle_converter(const char *args) {
    if (!args) { log_error("Usage: converter <length|temp|check_bit|to_binary> ..."); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " "), *v1s = strtok(NULL, " "), *v2s = strtok(NULL, " "), *v3s = strtok(NULL, " ");
    if (!op || !v1s) { log_error("Usage: converter <op> <value> ..."); return; }
    
    if (strcmp(op, "check_bit") == 0) {
        int v1;
        if (sscanf(v1s, "%d", &v1) != 1) { log_error("Invalid integer format"); return; }
        if (!v2s) { log_error("Usage: converter check_bit <value> <bit>"); return; }
        int bit;
        if (sscanf(v2s, "%d", &bit) != 1) { log_error("Invalid bit position"); return; }
        print_result(converter_check_bit(v1, bit));
    } else if (strcmp(op, "to_binary") == 0) {
        int v1;
        if (sscanf(v1s, "%d", &v1) != 1) { log_error("Invalid integer format"); return; }
        print_result(converter_to_binary(v1));
    } else if (strcmp(op, "length") == 0) {
        // converter length 100 cm m
        if (!v2s || !v3s) { log_error("Usage: converter length <value> <from> <to>"); return; }
        double val;
        if (sscanf(v1s, "%lf", &val) != 1) { log_error("Invalid number format"); return; }
        print_result(converter_length(val, v2s, v3s));
    } else if (strcmp(op, "temp") == 0) {
        // converter temp 100 C F
        if (!v2s || !v3s) { log_error("Usage: converter temp <value> <from> <to>"); return; }
        double val;
        if (sscanf(v1s, "%lf", &val) != 1) { log_error("Invalid number format"); return; }
        print_result(converter_temperature(val, v2s, v3s));
    } else {
        log_error("Unknown converter operation. Use: length, temp, check_bit, to_binary");
    }
}

void handle_graphical(const char *args) {
    if (!args) { log_error("Usage: graphical plot <expression>"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: graphical plot <expression>"); return; }
    if (strcmp(op, "plot") == 0) {
        char *expr = strtok(NULL, "");
        if (expr) graphical_plot(expr);
        else log_error("Usage: graphical plot <expression>");
    } else {
        log_error("Unknown graphical operation. Use: plot");
    }
}

void handle_calculus(const char *args) {
    if (!args) { log_error("Usage: calculus integral <expr> <a> <b> [n]"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: calculus integral <expr> <a> <b> [n]"); return; }
    if (strcmp(op, "integral") == 0) {
        char *expr = strtok(NULL, " "), *as = strtok(NULL, " "), *bs = strtok(NULL, " "), *ns = strtok(NULL, " ");
        if (!expr || !as || !bs) { log_error("Usage: calculus integral <expr> <a> <b> [n]"); return; }
        double a, b;
        if (sscanf(as, "%lf", &a) != 1 || sscanf(bs, "%lf", &b) != 1) {
            log_error("Invalid number format"); return;
        }
        int n = 1000;
        if (ns && sscanf(ns, "%d", &n) != 1) { log_error("Invalid step count"); return; }
        print_result(calculus_integral(expr, a, b, n));
    } else {
        log_error("Unknown calculus operation. Use: integral");
    }
}

void handle_solver(const char *args) {
    if (!args) { log_error("Usage: solver matrix_det <a> <b> <c> <d>"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: solver matrix_det <a> <b> <c> <d>"); return; }
    if (strcmp(op, "matrix_det") == 0) {
        double m[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                char *s = strtok(NULL, " ");
                if (!s) { log_error("Usage: solver matrix_det <a> <b> <c> <d>"); return; }
                if (sscanf(s, "%lf", &m[i][j]) != 1) { log_error("Invalid number format"); return; }
            }
        }
        print_result(solver_matrix_det2x2(m));
    } else {
        log_error("Unknown solver operation. Use: matrix_det");
    }
}

void handle_extra(const char *args) {
    if (!args) { log_error("Usage: extra save <value> <filename>"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: extra save <value> <filename>"); return; }
    if (strcmp(op, "save") == 0) {
        char *vs = strtok(NULL, " "), *fs = strtok(NULL, " ");
        if (!vs || !fs) { log_error("Usage: extra save <value> <filename>"); return; }
        double val;
        if (sscanf(vs, "%lf", &val) != 1) { log_error("Invalid number format"); return; }
        CalculationResult res = extra_save_result(val, fs);
        if (!res.is_error) log_success("Result saved to file.");
        else log_error(res.err_message);
    } else if (strcmp(op, "load") == 0) {
        char *fs = strtok(NULL, " ");
        if (!fs) { log_error("Usage: extra load <filename>"); return; }
        print_result(extra_load_data(fs));
    } else {
        log_error("Unknown extra operation. Use: save, load");
    }
}

// CONCEPT: Complex number handler
void handle_complex(const char *args) {
    if (!args) { log_error("Usage: complex <add|sub|mul|div> <a+bi> <c+di>"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " "), *z1s = strtok(NULL, " "), *z2s = strtok(NULL, " ");
    if (!op) { log_error("Usage: complex <add|sub|mul|div> <a+bi> <c+di>"); return; }
    
    if (strcmp(op, "mag") == 0) {
        if (!z1s) { log_error("Usage: complex mag <a+bi>"); return; }
        Complex z1;
        CalculationResult parse = complex_parse(z1s, &z1);
        if (parse.is_error) { log_error(parse.err_message); return; }
        CalculationResult res = {complex_magnitude(z1), false, ""};
        print_result(res);
        return;
    }
    
    if (!z1s || !z2s) { log_error("Usage: complex <add|sub|mul|div> <a+bi> <c+di>"); return; }
    
    Complex z1, z2, result;
    CalculationResult parse1 = complex_parse(z1s, &z1);
    CalculationResult parse2 = complex_parse(z2s, &z2);
    
    if (parse1.is_error) { log_error(parse1.err_message); return; }
    if (parse2.is_error) { log_error(parse2.err_message); return; }
    
    if (strcmp(op, "add") == 0) result = complex_add(z1, z2);
    else if (strcmp(op, "sub") == 0) result = complex_sub(z1, z2);
    else if (strcmp(op, "mul") == 0) result = complex_mul(z1, z2);
    else if (strcmp(op, "div") == 0) result = complex_div(z1, z2);
    else { log_error("Unknown operation. Use: add, sub, mul, div, mag"); return; }
    
    complex_print(result);
}

// CONCEPT: Financial operations handler
void handle_financial(const char *args) {
    if (!args) { log_error("Usage: financial <npv|compound> ..."); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: financial <npv|compound> ..."); return; }
    
    if (strcmp(op, "npv") == 0) {
        // financial npv <rate> <cf0> <cf1> ...
        char *rates = strtok(NULL, " ");
        if (!rates) { log_error("Usage: financial npv <rate> <cashflows...>"); return; }
        double rate;
        if (sscanf(rates, "%lf", &rate) != 1) { log_error("Invalid rate"); return; }
        
        int cap = 10, count = 0;
        double *cfs = malloc(cap * sizeof(double));
        if (!cfs) { log_error("Memory allocation failed"); return; }
        
        char *t = strtok(NULL, " ");
        while (t) {
            if (count >= cap) {
                cap *= 2;
                double *new_cfs = realloc(cfs, cap * sizeof(double));
                if (!new_cfs) { free(cfs); log_error("Memory allocation failed"); return; }
                cfs = new_cfs;
            }
            if (sscanf(t, "%lf", &cfs[count]) == 1) count++;
            t = strtok(NULL, " ");
        }
        
        if (count == 0) { free(cfs); log_error("No cashflows provided"); return; }
        print_result(financial_npv(rate, cfs, count));
        free(cfs);
    } else if (strcmp(op, "compound") == 0) {
        // financial compound <principal> <rate> <periods>
        char *ps = strtok(NULL, " "), *rs = strtok(NULL, " "), *ns = strtok(NULL, " ");
        if (!ps || !rs || !ns) { log_error("Usage: financial compound <principal> <rate> <periods>"); return; }
        double principal, rate;
        int periods;
        if (sscanf(ps, "%lf", &principal) != 1) { log_error("Invalid principal"); return; }
        if (sscanf(rs, "%lf", &rate) != 1) { log_error("Invalid rate"); return; }
        if (sscanf(ns, "%d", &periods) != 1) { log_error("Invalid periods"); return; }
        print_result(financial_compound_interest(principal, rate, periods));
    } else {
        log_error("Unknown operation. Use: npv, compound");
    }
}

// CONCEPT: Programming/scripting handler with function pointers
void handle_programming(const char *args) {
    if (!args) { log_error("Usage: programming <list|run> [script] [args...]"); return; }
    char copy[MAX_CMD_LEN];
    strncpy(copy, args, MAX_CMD_LEN - 1);
    copy[MAX_CMD_LEN - 1] = '\0';
    char *op = strtok(copy, " ");
    if (!op) { log_error("Usage: programming <list|run> [script] [args...]"); return; }
    
    if (strcmp(op, "list") == 0) {
        programming_list_scripts();
    } else if (strcmp(op, "run") == 0) {
        char *script = strtok(NULL, " ");
        if (!script) { log_error("Usage: programming run <script> [args...]"); return; }
        
        int cap = 10, count = 0;
        double *args_arr = malloc(cap * sizeof(double));
        if (!args_arr) { log_error("Memory allocation failed"); return; }
        
        char *t = strtok(NULL, " ");
        while (t) {
            if (count >= cap) {
                cap *= 2;
                double *new_args = realloc(args_arr, cap * sizeof(double));
                if (!new_args) { free(args_arr); log_error("Memory allocation failed"); return; }
                args_arr = new_args;
            }
            if (sscanf(t, "%lf", &args_arr[count]) == 1) count++;
            t = strtok(NULL, " ");
        }
        
        print_result(programming_execute(script, args_arr, count));
        free(args_arr);
    } else {
        log_error("Unknown operation. Use: list, run");
    }
}
