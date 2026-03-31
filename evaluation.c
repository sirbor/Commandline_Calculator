#include "evaluation.h"
#include "ops/scientific_ops.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

// CONCEPT: Recursive descent or simple parsing (Day 6/8)
// For simplicity, let's support a few hardcoded expressions
CalculationResult evaluate_expression(const char *expr, double x_val) {
    CalculationResult res = {0.0, false, ""};
    
    // CONCEPT: String parsing (Day 7) - support basic functions
    if (strcmp(expr, "sin(x)") == 0) {
        res = scientific_sin(x_val, false);
    } else if (strcmp(expr, "cos(x)") == 0) {
        res = scientific_cos(x_val, false);
    } else if (strcmp(expr, "x") == 0) {
        res.value = x_val;
    } else if (strcmp(expr, "x^2") == 0) {
        res.value = x_val * x_val;
    } else {
        res.is_error = true;
        strcpy(res.err_message, "Unsupported expression. Try: sin(x), cos(x), x, x^2");
    }
    
    return res;
}
