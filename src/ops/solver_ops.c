#include "ops/solver_ops.h"
#include "evaluation.h"
#include <string.h>
#include <math.h>

// ==================== Matrix Operations ====================

CalculationResult solver_matrix_det2x2(double m[2][2]) {
    CalculationResult res;
    res.value = (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult solver_matrix_det3x3(double m[3][3]) {
    CalculationResult res;
    double det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
               - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
               + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    res.value = det;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult solver_matrix_trace(double *m, int n) {
    CalculationResult res;
    if (n <= 0 || m == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Invalid matrix.");
        return res;
    }
    
    double trace = 0;
    for (int i = 0; i < n; i++) {
        trace += m[i * n + i];
    }
    
    res.value = trace;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// ==================== Quadratic Equation Solver ====================

QuadraticResult solver_quadratic(double a, double b, double c) {
    QuadraticResult res;
    res.is_complex = false;
    res.has_solution = true;
    strcpy(res.message, "");
    
    if (fabs(a) < 1e-15) {
        if (fabs(b) < 1e-15) {
            res.has_solution = false;
            strcpy(res.message, "Not a valid equation (a=0, b=0).");
            return res;
        }
        res.x1 = -c / b;
        res.x2 = res.x1;
        strcpy(res.message, "Linear equation (a=0): single solution.");
        return res;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        double sqrt_d = sqrt(discriminant);
        res.x1 = (-b + sqrt_d) / (2 * a);
        res.x2 = (-b - sqrt_d) / (2 * a);
        strcpy(res.message, "Two real roots.");
    } else if (fabs(discriminant) < 1e-15) {
        res.x1 = -b / (2 * a);
        res.x2 = res.x1;
        strcpy(res.message, "One repeated real root.");
    } else {
        res.is_complex = true;
        double real_part = -b / (2 * a);
        double imag_part = sqrt(-discriminant) / (2 * a);
        res.x1 = real_part;
        res.x2 = imag_part;
        strcpy(res.message, "Two complex roots.");
    }
    
    return res;
}

// ==================== Linear System Solvers ====================

LinearSystem2Result solver_linear_system_2x2(double a1, double b1, double c1,
                                              double a2, double b2, double c2) {
    LinearSystem2Result res;
    res.has_solution = true;
    strcpy(res.message, "");
    
    double det = a1 * b2 - a2 * b1;
    
    if (fabs(det) < 1e-15) {
        res.has_solution = false;
        res.x = 0;
        res.y = 0;
        if (fabs(a1 * c2 - a2 * c1) < 1e-15 && fabs(b1 * c2 - b2 * c1) < 1e-15) {
            strcpy(res.message, "Infinite solutions (dependent equations).");
        } else {
            strcpy(res.message, "No solution (inconsistent system).");
        }
        return res;
    }
    
    res.x = (c1 * b2 - c2 * b1) / det;
    res.y = (a1 * c2 - a2 * c1) / det;
    strcpy(res.message, "Unique solution found.");
    return res;
}

LinearSystem3Result solver_linear_system_3x3(double coeffs[3][4]) {
    LinearSystem3Result res;
    res.has_solution = true;
    strcpy(res.message, "");
    
    double a[3][4];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = coeffs[i][j];
        }
    }
    
    for (int col = 0; col < 3; col++) {
        int max_row = col;
        for (int row = col + 1; row < 3; row++) {
            if (fabs(a[row][col]) > fabs(a[max_row][col])) {
                max_row = row;
            }
        }
        
        for (int j = 0; j < 4; j++) {
            double temp = a[col][j];
            a[col][j] = a[max_row][j];
            a[max_row][j] = temp;
        }
        
        if (fabs(a[col][col]) < 1e-15) {
            res.has_solution = false;
            res.x = res.y = res.z = 0;
            strcpy(res.message, "No unique solution (singular matrix).");
            return res;
        }
        
        for (int row = col + 1; row < 3; row++) {
            double factor = a[row][col] / a[col][col];
            for (int j = col; j < 4; j++) {
                a[row][j] -= factor * a[col][j];
            }
        }
    }
    
    res.z = a[2][3] / a[2][2];
    res.y = (a[1][3] - a[1][2] * res.z) / a[1][1];
    res.x = (a[0][3] - a[0][2] * res.z - a[0][1] * res.y) / a[0][0];
    
    strcpy(res.message, "Unique solution found.");
    return res;
}

// ==================== Root Finding ====================

CalculationResult solver_bisection(const char *expr, double a, double b, double tol, int max_iter) {
    CalculationResult res;
    
    CalculationResult fa = evaluate_expression(expr, a);
    CalculationResult fb = evaluate_expression(expr, b);
    
    if (fa.is_error || fb.is_error) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Error evaluating expression at bounds.");
        return res;
    }
    
    if (fa.value * fb.value > 0) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Function must have opposite signs at bounds.");
        return res;
    }
    
    double c = a;
    for (int i = 0; i < max_iter; i++) {
        c = (a + b) / 2;
        CalculationResult fc = evaluate_expression(expr, c);
        
        if (fc.is_error) {
            res.value = 0;
            res.is_error = true;
            strcpy(res.err_message, "Error evaluating expression.");
            return res;
        }
        
        if (fabs(fc.value) < tol || (b - a) / 2 < tol) {
            res.value = c;
            res.is_error = false;
            strcpy(res.err_message, "");
            return res;
        }
        
        CalculationResult fa_new = evaluate_expression(expr, a);
        if (fc.value * fa_new.value < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    
    res.value = c;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult solver_newton_raphson(const char *expr, double x0, double tol, int max_iter) {
    CalculationResult res;
    double x = x0;
    double h = 1e-7;
    
    for (int i = 0; i < max_iter; i++) {
        CalculationResult fx = evaluate_expression(expr, x);
        if (fx.is_error) {
            res.value = 0;
            res.is_error = true;
            strcpy(res.err_message, "Error evaluating expression.");
            return res;
        }
        
        CalculationResult fx_plus = evaluate_expression(expr, x + h);
        CalculationResult fx_minus = evaluate_expression(expr, x - h);
        
        if (fx_plus.is_error || fx_minus.is_error) {
            res.value = 0;
            res.is_error = true;
            strcpy(res.err_message, "Error computing derivative.");
            return res;
        }
        
        double fpx = (fx_plus.value - fx_minus.value) / (2 * h);
        
        if (fabs(fpx) < 1e-15) {
            res.value = 0;
            res.is_error = true;
            strcpy(res.err_message, "Derivative is zero, cannot continue.");
            return res;
        }
        
        double x_new = x - fx.value / fpx;
        
        if (fabs(x_new - x) < tol) {
            res.value = x_new;
            res.is_error = false;
            strcpy(res.err_message, "");
            return res;
        }
        
        x = x_new;
    }
    
    res.value = x;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// ==================== Polynomial Evaluation ====================

CalculationResult solver_poly_eval(double *coeffs, int degree, double x) {
    CalculationResult res;
    if (degree < 0 || coeffs == NULL) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Invalid polynomial.");
        return res;
    }
    
    double result = coeffs[0];
    for (int i = 1; i <= degree; i++) {
        result = result * x + coeffs[i];
    }
    
    res.value = result;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}
