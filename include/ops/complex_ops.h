#ifndef COMPLEX_OPS_H
#define COMPLEX_OPS_H

#include "common.h"

// CONCEPT: Complex number operations using struct (Day 15)
Complex complex_add(Complex a, Complex b);
Complex complex_sub(Complex a, Complex b);
Complex complex_mul(Complex a, Complex b);
Complex complex_div(Complex a, Complex b);
double complex_magnitude(Complex z);
CalculationResult complex_parse(const char *str, Complex *out);
void complex_print(Complex z);

#endif // COMPLEX_OPS_H
