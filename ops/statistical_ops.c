#include "ops/statistical_ops.h"
#include <math.h>
#include <string.h>

// CONCEPT: 1D Array processing
CalculationResult statistical_mean(double *data, int n) {
    CalculationResult res;
    if (n <= 0) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    
    res.value = sum / n;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_stddev(double *data, int n) {
    CalculationResult res;
    if (n <= 1) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Standard deviation requires at least 2 points.");
        return res;
    }
    
    CalculationResult mean_res = statistical_mean(data, n);
    double mean = mean_res.value;
    double sum_sq_diff = 0;
    
    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow(data[i] - mean, 2);
    }
    
    res.value = sqrt(sum_sq_diff / (n - 1));
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}
