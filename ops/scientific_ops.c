#include "ops/scientific_ops.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// CONCEPT: Trig math with degree/radian conversion
CalculationResult scientific_sin(double x, bool is_deg) {
    double val = is_deg ? x * (M_PI / 180.0) : x;
    CalculationResult res = { sin(val), false, "" };
    return res;
}

CalculationResult scientific_cos(double x, bool is_deg) {
    double val = is_deg ? x * (M_PI / 180.0) : x;
    CalculationResult res = { cos(val), false, "" };
    return res;
}

// CONCEPT: Recursion - a function calling itself
static double recursive_factorial(int n) {
    if (n <= 1) return 1.0;
    return n * recursive_factorial(n - 1);
}

CalculationResult scientific_factorial(int n) {
    CalculationResult res;
    if (n < 0) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Factorial of negative number is undefined.");
    } else {
        res.value = recursive_factorial(n);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}
