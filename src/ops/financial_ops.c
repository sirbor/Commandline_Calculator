#include "ops/financial_ops.h"
#include <math.h>
#include <string.h>

// CONCEPT: Net Present Value - loops and precision (README)
// NPV = sum of cashflows[i] / (1 + rate)^i
CalculationResult financial_npv(double rate, double *cashflows, int n) {
    CalculationResult res = {0.0, false, ""};
    
    if (n <= 0) {
        res.is_error = true;
        strcpy(res.err_message, "Need at least one cashflow.");
        return res;
    }
    
    if (rate <= -1.0) {
        res.is_error = true;
        strcpy(res.err_message, "Rate must be greater than -100%.");
        return res;
    }
    
    double npv = 0.0;
    // CONCEPT: Loop with floating-point precision
    for (int i = 0; i < n; i++) {
        npv += cashflows[i] / pow(1.0 + rate, i);
    }
    
    res.value = npv;
    return res;
}

// CONCEPT: Iterative approximation - finding IRR using Newton-Raphson-like method
CalculationResult financial_irr(double *cashflows, int n) {
    CalculationResult res = {0.0, false, ""};
    
    if (n <= 1) {
        res.is_error = true;
        strcpy(res.err_message, "Need at least two cashflows for IRR.");
        return res;
    }
    
    // CONCEPT: Numerical approximation with iteration
    double rate = 0.1; // Initial guess
    double tolerance = 1e-7;
    int max_iterations = 1000;
    
    for (int iter = 0; iter < max_iterations; iter++) {
        double npv = 0.0;
        double dnpv = 0.0; // Derivative
        
        for (int i = 0; i < n; i++) {
            double factor = pow(1.0 + rate, i);
            npv += cashflows[i] / factor;
            if (i > 0) {
                dnpv -= i * cashflows[i] / (factor * (1.0 + rate));
            }
        }
        
        if (fabs(npv) < tolerance) {
            res.value = rate * 100.0; // Return as percentage
            return res;
        }
        
        if (fabs(dnpv) < tolerance) {
            break; // Avoid division by zero
        }
        
        rate = rate - npv / dnpv;
    }
    
    res.is_error = true;
    strcpy(res.err_message, "IRR did not converge.");
    return res;
}

// CONCEPT: Compound interest formula A = P(1 + r)^n
CalculationResult financial_compound_interest(double principal, double rate, int periods) {
    CalculationResult res = {0.0, false, ""};
    
    if (principal < 0 || periods < 0) {
        res.is_error = true;
        strcpy(res.err_message, "Principal and periods must be non-negative.");
        return res;
    }
    
    res.value = principal * pow(1.0 + rate, periods);
    return res;
}

CalculationResult financial_pmt(double rate, int periods, double present_value) {
    CalculationResult res = {0.0, false, ""};
    if (periods <= 0) {
        res.is_error = true;
        strcpy(res.err_message, "Periods must be positive.");
        return res;
    }
    if (rate == 0.0) {
        res.value = -present_value / periods;
    } else {
        res.value = -(present_value * rate) / (1 - pow(1 + rate, -periods));
    }
    return res;
}

CalculationResult financial_fv(double rate, int periods, double pmt, double present_value) {
    CalculationResult res = {0.0, false, ""};
    if (periods < 0) {
        res.is_error = true;
        strcpy(res.err_message, "Periods must be non-negative.");
        return res;
    }
    if (rate == 0.0) {
        res.value = -(present_value + pmt * periods);
    } else {
        res.value = -(present_value * pow(1 + rate, periods) + pmt * (pow(1 + rate, periods) - 1) / rate);
    }
    return res;
}

CalculationResult financial_pv(double rate, int periods, double pmt, double future_value) {
    CalculationResult res = {0.0, false, ""};
    if (periods < 0) {
        res.is_error = true;
        strcpy(res.err_message, "Periods must be non-negative.");
        return res;
    }
    if (rate == 0.0) {
        res.value = -(future_value + pmt * periods);
    } else {
        res.value = -(future_value / pow(1 + rate, periods) + pmt * (1 - pow(1 + rate, -periods)) / rate);
    }
    return res;
}
