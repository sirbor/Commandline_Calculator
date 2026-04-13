#include "ops/basic_ops.h"
#include <string.h>
#include <math.h>
#include <float.h>

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

// Modulo operation (works with floating point)
CalculationResult basic_mod(double a, double b) {
    CalculationResult res;
    if (b == 0.0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Modulo by zero is not allowed.");
    } else {
        res.value = fmod(a, b);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

// Power operation
CalculationResult basic_pow(double base, double exp) {
    CalculationResult res;
    double result = pow(base, exp);
    if (isnan(result) || isinf(result)) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Power operation resulted in invalid value.");
    } else {
        res.value = result;
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

// Absolute value
CalculationResult basic_abs(double a) {
    CalculationResult res = { fabs(a), false, "" };
    return res;
}

// Percentage: calculates 'percent' % of 'value'
CalculationResult basic_percent(double value, double percent) {
    CalculationResult res = { value * (percent / 100.0), false, "" };
    return res;
}

// Square root
CalculationResult basic_sqrt(double a) {
    CalculationResult res;
    if (a < 0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Cannot compute square root of negative number.");
    } else {
        res.value = sqrt(a);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

// Sum of multiple numbers
CalculationResult basic_sum(double *values, int count) {
    CalculationResult res;
    if (count <= 0 || values == NULL) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "No values provided for sum.");
        return res;
    }
    
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    
    res.value = sum;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// Product of multiple numbers
CalculationResult basic_product(double *values, int count) {
    CalculationResult res;
    if (count <= 0 || values == NULL) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "No values provided for product.");
        return res;
    }
    
    double product = 1.0;
    for (int i = 0; i < count; i++) {
        product *= values[i];
    }
    
    res.value = product;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// Average of multiple numbers
CalculationResult basic_avg(double *values, int count) {
    CalculationResult res;
    if (count <= 0 || values == NULL) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "No values provided for average.");
        return res;
    }
    
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    
    res.value = sum / count;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// Minimum of multiple numbers
CalculationResult basic_min(double *values, int count) {
    CalculationResult res;
    if (count <= 0 || values == NULL) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "No values provided for min.");
        return res;
    }
    
    double min_val = values[0];
    for (int i = 1; i < count; i++) {
        if (values[i] < min_val) {
            min_val = values[i];
        }
    }
    
    res.value = min_val;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// Maximum of multiple numbers
CalculationResult basic_max(double *values, int count) {
    CalculationResult res;
    if (count <= 0 || values == NULL) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "No values provided for max.");
        return res;
    }
    
    double max_val = values[0];
    for (int i = 1; i < count; i++) {
        if (values[i] > max_val) {
            max_val = values[i];
        }
    }
    
    res.value = max_val;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}
