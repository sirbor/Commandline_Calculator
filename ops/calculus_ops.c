#include "ops/calculus_ops.h"
#include "evaluation.h"
#include <string.h>

// CONCEPT: Numerical Integration - Trapezoidal Rule
CalculationResult calculus_integral(const char *expr, double a, double b, int n) {
    CalculationResult res = {0.0, false, ""};
    
    if (n <= 0) {
        res.is_error = true;
        strcpy(res.err_message, "Number of intervals must be positive.");
        return res;
    }
    
    double h = (b - a) / n;
    double sum = 0.0;
    
    // Evaluate at endpoints
    CalculationResult fa = evaluate_expression(expr, a);
    CalculationResult fb = evaluate_expression(expr, b);
    
    if (fa.is_error || fb.is_error) {
        res.is_error = true;
        strcpy(res.err_message, "Evaluation error at boundary.");
        return res;
    }
    
    sum = (fa.value + fb.value) / 2.0;
    
    // Evaluate at interior points
    for (int i = 1; i < n; i++) {
        CalculationResult fi = evaluate_expression(expr, a + i * h);
        if (fi.is_error) {
            res.is_error = true;
            strcpy(res.err_message, "Evaluation error in interval.");
            return res;
        }
        sum += fi.value;
    }
    
    res.value = sum * h;
    return res;
}
