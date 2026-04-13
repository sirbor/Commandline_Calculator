#ifndef STATISTICAL_OPS_H
#define STATISTICAL_OPS_H

#include "common.h"

// Central tendency
CalculationResult statistical_mean(double *data, int n);
CalculationResult statistical_median(double *data, int n);
CalculationResult statistical_mode(double *data, int n);

// Dispersion measures
CalculationResult statistical_stddev(double *data, int n);
CalculationResult statistical_variance(double *data, int n);
CalculationResult statistical_range(double *data, int n);

// Aggregate functions
CalculationResult statistical_sum(double *data, int n);
CalculationResult statistical_min(double *data, int n);
CalculationResult statistical_max(double *data, int n);
CalculationResult statistical_count(double *data, int n);

// Percentiles
CalculationResult statistical_percentile(double *data, int n, double p);
CalculationResult statistical_quartiles(double *data, int n, double *q1, double *q2, double *q3);

// Correlation
CalculationResult statistical_covariance(double *x, double *y, int n);
CalculationResult statistical_correlation(double *x, double *y, int n);

// Regression
CalculationResult statistical_linear_regression_slope(double *x, double *y, int n);
CalculationResult statistical_linear_regression_intercept(double *x, double *y, int n);

#endif // STATISTICAL_OPS_H
