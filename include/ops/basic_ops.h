#ifndef BASIC_OPS_H
#define BASIC_OPS_H

#include "common.h"

// CONCEPT: Arithmetic operators - implementation of basic math
CalculationResult basic_add(double a, double b);
CalculationResult basic_sub(double a, double b);
CalculationResult basic_mul(double a, double b);
CalculationResult basic_div(double a, double b);

// Extended basic operations
CalculationResult basic_mod(double a, double b);
CalculationResult basic_pow(double base, double exp);
CalculationResult basic_abs(double a);
CalculationResult basic_percent(double value, double percent);
CalculationResult basic_sqrt(double a);

// Multi-number operations
CalculationResult basic_sum(double *values, int count);
CalculationResult basic_product(double *values, int count);
CalculationResult basic_avg(double *values, int count);
CalculationResult basic_min(double *values, int count);
CalculationResult basic_max(double *values, int count);

#endif // BASIC_OPS_H
