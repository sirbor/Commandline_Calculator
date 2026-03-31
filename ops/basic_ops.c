#include "ops/basic_ops.h"
#include <string.h>

// CONCEPT: Arithmetic, relational, and assignment operators (Day 4)
CalculationResult basic_add(double a, double b) {
    CalculationResult res = { a + b, false, "" };
    return res;
}

CalculationResult basic_sub(double a, double b) {
    CalculationResult res = { a - b, false, "" };
    return res;
}

CalculationResult basic_mul(double a, double b) {
    CalculationResult res = { a * b, false, "" };
    return res;
}

// CONCEPT: Logical operator and conditional for division by zero safety
CalculationResult basic_div(double a, double b) {
    CalculationResult res;
    if (b == 0.0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Division by zero is not allowed.");
    } else {
        res.value = a / b;
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}
