#ifndef FINANCIAL_OPS_H
#define FINANCIAL_OPS_H

#include "common.h"

// CONCEPT: Financial calculations with precision (Day 31)
CalculationResult financial_npv(double rate, double *cashflows, int n);
CalculationResult financial_irr(double *cashflows, int n);
CalculationResult financial_compound_interest(double principal, double rate, int periods);

#endif // FINANCIAL_OPS_H
