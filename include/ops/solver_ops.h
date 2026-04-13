#ifndef SOLVER_OPS_H
#define SOLVER_OPS_H

#include "common.h"

// Matrix operations
CalculationResult solver_matrix_det2x2(double m[2][2]);
CalculationResult solver_matrix_det3x3(double m[3][3]);
CalculationResult solver_matrix_trace(double *m, int n);

// Equation solvers
typedef struct {
    double x1;
    double x2;
    bool is_complex;
    bool has_solution;
    char message[MAX_ERR_LEN];
} QuadraticResult;

QuadraticResult solver_quadratic(double a, double b, double c);

typedef struct {
    double x;
    double y;
    bool has_solution;
    char message[MAX_ERR_LEN];
} LinearSystem2Result;

LinearSystem2Result solver_linear_system_2x2(double a1, double b1, double c1,
                                              double a2, double b2, double c2);

typedef struct {
    double x;
    double y;
    double z;
    bool has_solution;
    char message[MAX_ERR_LEN];
} LinearSystem3Result;

LinearSystem3Result solver_linear_system_3x3(double coeffs[3][4]);

// Root finding
CalculationResult solver_bisection(const char *expr, double a, double b, double tol, int max_iter);
CalculationResult solver_newton_raphson(const char *expr, double x0, double tol, int max_iter);

// Polynomial evaluation
CalculationResult solver_poly_eval(double *coeffs, int degree, double x);

#endif // SOLVER_OPS_H
