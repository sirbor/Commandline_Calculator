#ifndef SCIENTIFIC_OPS_H
#define SCIENTIFIC_OPS_H

#include "common.h"

// Trigonometric functions
CalculationResult scientific_sin(double x, bool is_deg);
CalculationResult scientific_cos(double x, bool is_deg);
CalculationResult scientific_tan(double x, bool is_deg);
CalculationResult scientific_asin(double x);
CalculationResult scientific_acos(double x);
CalculationResult scientific_atan(double x);

// Hyperbolic functions
CalculationResult scientific_sinh(double x);
CalculationResult scientific_cosh(double x);
CalculationResult scientific_tanh(double x);
CalculationResult scientific_asinh(double x);
CalculationResult scientific_acosh(double x);
CalculationResult scientific_atanh(double x);

// Logarithmic and exponential
CalculationResult scientific_log(double x);
CalculationResult scientific_log10(double x);
CalculationResult scientific_log2(double x);
CalculationResult scientific_log_base(double x, double base);
CalculationResult scientific_exp(double x);

// Roots
CalculationResult scientific_sqrt(double x);
CalculationResult scientific_cbrt(double x);
CalculationResult scientific_nroot(double x, double n);

// Factorial, permutations, combinations
CalculationResult scientific_factorial(int n);
CalculationResult scientific_permutation(int n, int r);
CalculationResult scientific_combination(int n, int r);

// Number theory
CalculationResult scientific_gcd(long long a, long long b);
CalculationResult scientific_lcm(long long a, long long b);
CalculationResult scientific_isprime(long long n);

// Other
CalculationResult scientific_rand(void);
CalculationResult scientific_floor(double x);
CalculationResult scientific_ceil(double x);
CalculationResult scientific_round(double x);
CalculationResult scientific_deg2rad(double deg);
CalculationResult scientific_rad2deg(double rad);

#endif // SCIENTIFIC_OPS_H
