#include "ops/statistical_ops.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Helper: compare function for qsort
static int compare_doubles(const void *a, const void *b) {
    double diff = (*(double*)a) - (*(double*)b);
    return (diff > 0) - (diff < 0);
}

// Helper: create sorted copy of data
static double* sorted_copy(double *data, int n) {
    double *sorted = malloc(n * sizeof(double));
    if (!sorted) return NULL;
    memcpy(sorted, data, n * sizeof(double));
    qsort(sorted, n, sizeof(double), compare_doubles);
    return sorted;
}

// ==================== Central Tendency ====================

CalculationResult statistical_mean(double *data, int n) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
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

CalculationResult statistical_median(double *data, int n) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    
    double *sorted = sorted_copy(data, n);
    if (!sorted) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Memory allocation failed.");
        return res;
    }
    
    if (n % 2 == 0) {
        res.value = (sorted[n/2 - 1] + sorted[n/2]) / 2.0;
    } else {
        res.value = sorted[n/2];
    }
    
    free(sorted);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_mode(double *data, int n) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    
    double *sorted = sorted_copy(data, n);
    if (!sorted) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Memory allocation failed.");
        return res;
    }
    
    double mode = sorted[0];
    int max_count = 1, current_count = 1;
    
    for (int i = 1; i < n; i++) {
        if (fabs(sorted[i] - sorted[i-1]) < 1e-10) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                mode = sorted[i-1];
            }
            current_count = 1;
        }
    }
    
    if (current_count > max_count) {
        mode = sorted[n-1];
    }
    
    free(sorted);
    res.value = mode;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// ==================== Dispersion Measures ====================

CalculationResult statistical_variance(double *data, int n) {
    CalculationResult res;
    if (n <= 1 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Variance requires at least 2 data points.");
        return res;
    }
    
    CalculationResult mean_res = statistical_mean(data, n);
    double mean = mean_res.value;
    double sum_sq_diff = 0;
    
    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow(data[i] - mean, 2);
    }
    
    res.value = sum_sq_diff / (n - 1);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_stddev(double *data, int n) {
    CalculationResult var_res = statistical_variance(data, n);
    CalculationResult res;
    
    if (var_res.is_error) {
        return var_res;
    }
    
    res.value = sqrt(var_res.value);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_range(double *data, int n) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    
    double min_val = data[0], max_val = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] < min_val) min_val = data[i];
        if (data[i] > max_val) max_val = data[i];
    }
    
    res.value = max_val - min_val;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// ==================== Aggregate Functions ====================

CalculationResult statistical_sum(double *data, int n) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    
    res.value = sum;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_min(double *data, int n) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    
    double min_val = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] < min_val) min_val = data[i];
    }
    
    res.value = min_val;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_max(double *data, int n) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    
    double max_val = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > max_val) max_val = data[i];
    }
    
    res.value = max_val;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_count(double *data, int n) {
    (void)data;
    CalculationResult res = { (double)n, false, "" };
    return res;
}

// ==================== Percentiles ====================

CalculationResult statistical_percentile(double *data, int n, double p) {
    CalculationResult res;
    if (n <= 0 || data == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Empty dataset.");
        return res;
    }
    if (p < 0 || p > 100) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Percentile must be between 0 and 100.");
        return res;
    }
    
    double *sorted = sorted_copy(data, n);
    if (!sorted) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Memory allocation failed.");
        return res;
    }
    
    double index = (p / 100.0) * (n - 1);
    int lower = (int)floor(index);
    int upper = (int)ceil(index);
    
    if (lower == upper) {
        res.value = sorted[lower];
    } else {
        double fraction = index - lower;
        res.value = sorted[lower] + fraction * (sorted[upper] - sorted[lower]);
    }
    
    free(sorted);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_quartiles(double *data, int n, double *q1, double *q2, double *q3) {
    CalculationResult res;
    CalculationResult p25 = statistical_percentile(data, n, 25);
    CalculationResult p50 = statistical_percentile(data, n, 50);
    CalculationResult p75 = statistical_percentile(data, n, 75);
    
    if (p25.is_error || p50.is_error || p75.is_error) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Failed to compute quartiles.");
        return res;
    }
    
    *q1 = p25.value;
    *q2 = p50.value;
    *q3 = p75.value;
    
    res.value = p50.value;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// ==================== Correlation ====================

CalculationResult statistical_covariance(double *x, double *y, int n) {
    CalculationResult res;
    if (n <= 1 || x == NULL || y == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Covariance requires at least 2 paired data points.");
        return res;
    }
    
    double mean_x = 0, mean_y = 0;
    for (int i = 0; i < n; i++) {
        mean_x += x[i];
        mean_y += y[i];
    }
    mean_x /= n;
    mean_y /= n;
    
    double cov = 0;
    for (int i = 0; i < n; i++) {
        cov += (x[i] - mean_x) * (y[i] - mean_y);
    }
    
    res.value = cov / (n - 1);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_correlation(double *x, double *y, int n) {
    CalculationResult res;
    if (n <= 1 || x == NULL || y == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Correlation requires at least 2 paired data points.");
        return res;
    }
    
    CalculationResult cov_res = statistical_covariance(x, y, n);
    CalculationResult stdx = statistical_stddev(x, n);
    CalculationResult stdy = statistical_stddev(y, n);
    
    if (cov_res.is_error || stdx.is_error || stdy.is_error) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Failed to compute correlation.");
        return res;
    }
    
    if (stdx.value == 0 || stdy.value == 0) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Standard deviation is zero, correlation undefined.");
        return res;
    }
    
    res.value = cov_res.value / (stdx.value * stdy.value);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// ==================== Linear Regression ====================

CalculationResult statistical_linear_regression_slope(double *x, double *y, int n) {
    CalculationResult res;
    if (n <= 1 || x == NULL || y == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Regression requires at least 2 paired data points.");
        return res;
    }
    
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    
    double denom = n * sum_x2 - sum_x * sum_x;
    if (fabs(denom) < 1e-15) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Cannot compute slope (all x values are identical).");
        return res;
    }
    
    res.value = (n * sum_xy - sum_x * sum_y) / denom;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult statistical_linear_regression_intercept(double *x, double *y, int n) {
    CalculationResult res;
    CalculationResult slope_res = statistical_linear_regression_slope(x, y, n);
    
    if (slope_res.is_error) {
        return slope_res;
    }
    
    double mean_x = 0, mean_y = 0;
    for (int i = 0; i < n; i++) {
        mean_x += x[i];
        mean_y += y[i];
    }
    mean_x /= n;
    mean_y /= n;
    
    res.value = mean_y - slope_res.value * mean_x;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}
