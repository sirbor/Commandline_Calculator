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
    {"help", CMD_HELP, NULL},
    {"quit", CMD_QUIT, NULL},
    {NULL, CMD_UNKNOWN, NULL}
};

void handle_command(const char *command_str) {
    char cmd_line[MAX_CMD_LEN];
    strncpy(cmd_line, command_str, MAX_CMD_LEN);
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
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " "), *v1s = strtok(NULL, " "), *v2s = strtok(NULL, " ");
    if (!op || !v1s || !v2s) return;
    double v1, v2; sscanf(v1s, "%lf", &v1); sscanf(v2s, "%lf", &v2);
    CalculationResult res;
    if (strcmp(op, "add") == 0) res = basic_add(v1, v2);
    else if (strcmp(op, "sub") == 0) res = basic_sub(v1, v2);
    else if (strcmp(op, "mul") == 0) res = basic_mul(v1, v2);
    else if (strcmp(op, "div") == 0) res = basic_div(v1, v2);
    else return;
    print_result(res);
}

void handle_scientific(const char *args) {
    if (!args) return;
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " "), *v1s = strtok(NULL, " "), *v2s = strtok(NULL, " ");
    if (!op || !v1s) return;
    double v1; sscanf(v1s, "%lf", &v1);
    bool is_deg = (v2s && strcmp(v2s, "deg") == 0);
    CalculationResult res;
    if (strcmp(op, "sin") == 0) res = scientific_sin(v1, is_deg);
    else if (strcmp(op, "cos") == 0) res = scientific_cos(v1, is_deg);
    else if (strcmp(op, "fact") == 0) res = scientific_factorial((int)v1);
    else return;
    print_result(res);
}

void handle_memory(const char *args) {
    if (!args) return;
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " ");
    if (strcmp(op, "store") == 0) {
        char *vs = strtok(NULL, " ");
        if (!vs) return;
        double v; sscanf(vs, "%lf", &v); memory_store(v); log_success("Stored.");
    } else if (strcmp(op, "recall") == 0) print_result(memory_recall());
}

void handle_statistical(const char *args) {
    if (!args) return;
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " ");
    int cap = 10, count = 0; double *data = malloc(cap * sizeof(double));
    char *t = strtok(NULL, " ");
    while (t) {
        if (count >= cap) { cap *= 2; data = realloc(data, cap * sizeof(double)); }
        if (sscanf(t, "%lf", &data[count]) == 1) count++;
        t = strtok(NULL, " ");
    }
    CalculationResult res;
    if (strcmp(op, "mean") == 0) res = statistical_mean(data, count);
    else if (strcmp(op, "stddev") == 0) res = statistical_stddev(data, count);
    else { free(data); return; }
    print_result(res); free(data);
}

void handle_converter(const char *args) {
    if (!args) return;
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " "), *v1s = strtok(NULL, " "), *v2s = strtok(NULL, " ");
    if (!op || !v1s) return;
    int v1 = atoi(v1s);
    if (strcmp(op, "check_bit") == 0) {
        if (!v2s) return;
        print_result(converter_check_bit(v1, atoi(v2s)));
    } else if (strcmp(op, "to_binary") == 0) print_result(converter_to_binary(v1));
}

void handle_graphical(const char *args) {
    if (!args) return;
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " ");
    if (strcmp(op, "plot") == 0) {
        char *expr = strtok(NULL, "");
        if (expr) graphical_plot(expr);
    }
}

void handle_calculus(const char *args) {
    if (!args) return;
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " ");
    if (strcmp(op, "integral") == 0) {
        char *expr = strtok(NULL, " "), *as = strtok(NULL, " "), *bs = strtok(NULL, " "), *ns = strtok(NULL, " ");
        if (!expr || !as || !bs) return;
        double a = atof(as), b = atof(bs);
        int n = ns ? atoi(ns) : 1000;
        print_result(calculus_integral(expr, a, b, n));
    }
}

void handle_solver(const char *args) {
    if (!args) return;
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " ");
    if (strcmp(op, "matrix_det") == 0) {
        double m[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                char *s = strtok(NULL, " ");
                if (!s) return;
                m[i][j] = atof(s);
            }
        }
        print_result(solver_matrix_det2x2(m));
    }
}

void handle_extra(const char *args) {
    if (!args) { log_error("Usage: extra save <val> <filename>"); return; }
    char copy[MAX_CMD_LEN]; strncpy(copy, args, MAX_CMD_LEN);
    char *op = strtok(copy, " ");
    if (strcmp(op, "save") == 0) {
        char *vs = strtok(NULL, " "), *fs = strtok(NULL, " ");
        if (!vs || !fs) return;
        double val = atof(vs);
        CalculationResult res = extra_save_result(val, fs);
        if (!res.is_error) log_success("Result saved to file.");
        else log_error(res.err_message);
    }
}
