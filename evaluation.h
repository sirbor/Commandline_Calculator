#ifndef EVALUATION_H
#define EVALUATION_H

#include "common.h"

// CONCEPT: Expression evaluation and parsing (Day 6-7)
// This will handle parsing strings like "sin(x)" or "x^2 + 5"
CalculationResult evaluate_expression(const char *expr, double x_val);

#endif // EVALUATION_H
