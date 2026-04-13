#include "ops/scientific_ops.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// Helper: iterative factorial for large numbers (avoids stack overflow)
static double iterative_factorial(int n) {
    if (n <= 1) return 1.0;
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Helper: GCD using Euclidean algorithm
static long long gcd_helper(long long a, long long b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ==================== Trigonometric Functions ====================

CalculationResult scientific_sin(double x, bool is_deg) {
    double val = is_deg ? x * (M_PI / 180.0) : x;
    CalculationResult res = { sin(val), false, "" };
    return res;
}

CalculationResult scientific_cos(double x, bool is_deg) {
    double val = is_deg ? x * (M_PI / 180.0) : x;
    CalculationResult res = { cos(val), false, "" };
    return res;
}

CalculationResult scientific_tan(double x, bool is_deg) {
    double val = is_deg ? x * (M_PI / 180.0) : x;
    double cos_val = cos(val);
    CalculationResult res;
    if (fabs(cos_val) < 1e-15) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Tangent undefined at this angle (division by zero).");
    } else {
        res.value = tan(val);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_asin(double x) {
    CalculationResult res;
    if (x < -1.0 || x > 1.0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "asin input must be in range [-1, 1].");
    } else {
        res.value = asin(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_acos(double x) {
    CalculationResult res;
    if (x < -1.0 || x > 1.0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "acos input must be in range [-1, 1].");
    } else {
        res.value = acos(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_atan(double x) {
    CalculationResult res = { atan(x), false, "" };
    return res;
}

// ==================== Hyperbolic Functions ====================

CalculationResult scientific_sinh(double x) {
    CalculationResult res = { sinh(x), false, "" };
    return res;
}

CalculationResult scientific_cosh(double x) {
    CalculationResult res = { cosh(x), false, "" };
    return res;
}

CalculationResult scientific_tanh(double x) {
    CalculationResult res = { tanh(x), false, "" };
    return res;
}

CalculationResult scientific_asinh(double x) {
    CalculationResult res = { asinh(x), false, "" };
    return res;
}

CalculationResult scientific_acosh(double x) {
    CalculationResult res;
    if (x < 1.0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Domain error: acosh is only defined for x >= 1");
    } else {
        res.value = acosh(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_atanh(double x) {
    CalculationResult res;
    if (x <= -1.0 || x >= 1.0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Domain error: atanh is only defined for -1 < x < 1");
    } else {
        res.value = atanh(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

// ==================== Logarithmic and Exponential ====================

CalculationResult scientific_log(double x) {
    CalculationResult res;
    if (x <= 0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Logarithm undefined for non-positive values.");
    } else {
        res.value = log(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_log10(double x) {
    CalculationResult res;
    if (x <= 0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Logarithm undefined for non-positive values.");
    } else {
        res.value = log10(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_log2(double x) {
    CalculationResult res;
    if (x <= 0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Logarithm undefined for non-positive values.");
    } else {
        res.value = log2(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_log_base(double x, double base) {
    CalculationResult res;
    if (x <= 0 || base <= 0 || base == 1.0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Invalid arguments for log_base.");
    } else {
        res.value = log(x) / log(base);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_exp(double x) {
    double result = exp(x);
    CalculationResult res;
    if (isinf(result)) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Exponential overflow.");
    } else {
        res.value = result;
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

// ==================== Root Functions ====================

CalculationResult scientific_sqrt(double x) {
    CalculationResult res;
    if (x < 0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Square root of negative number is undefined.");
    } else {
        res.value = sqrt(x);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_cbrt(double x) {
    CalculationResult res = { cbrt(x), false, "" };
    return res;
}

CalculationResult scientific_nroot(double x, double n) {
    CalculationResult res;
    if (n == 0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Cannot compute 0th root.");
    } else if (x < 0 && fmod(n, 2.0) == 0) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Even root of negative number is undefined.");
    } else if (x < 0) {
        res.value = -pow(-x, 1.0 / n);
        res.is_error = false;
        strcpy(res.err_message, "");
    } else {
        res.value = pow(x, 1.0 / n);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

// ==================== Factorial, Permutations, Combinations ====================

CalculationResult scientific_factorial(int n) {
    CalculationResult res;
    if (n < 0) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Factorial of negative number is undefined.");
    } else if (n > 170) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Factorial overflow (max n=170).");
    } else {
        res.value = iterative_factorial(n);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_permutation(int n, int r) {
    CalculationResult res;
    if (n < 0 || r < 0) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "n and r must be non-negative.");
    } else if (r > n) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "r cannot be greater than n.");
    } else {
        double result = 1.0;
        for (int i = n; i > n - r; i--) {
            result *= i;
        }
        res.value = result;
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_combination(int n, int r) {
    CalculationResult res;
    if (n < 0 || r < 0) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "n and r must be non-negative.");
    } else if (r > n) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "r cannot be greater than n.");
    } else {
        if (r > n - r) r = n - r;
        double result = 1.0;
        for (int i = 0; i < r; i++) {
            result = result * (n - i) / (i + 1);
        }
        res.value = result;
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

// ==================== Number Theory ====================

CalculationResult scientific_gcd(long long a, long long b) {
    CalculationResult res;
    res.value = (double)gcd_helper(a, b);
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

CalculationResult scientific_lcm(long long a, long long b) {
    CalculationResult res;
    if (a == 0 || b == 0) {
        res.value = 0;
        res.is_error = false;
        strcpy(res.err_message, "");
    } else {
        long long abs_a = a < 0 ? -a : a;
        long long abs_b = b < 0 ? -b : b;
        res.value = (double)((abs_a / gcd_helper(a, b)) * abs_b);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

CalculationResult scientific_isprime(long long n) {
    CalculationResult res;
    if (n <= 1) {
        res.value = 0;
        res.is_error = false;
        strcpy(res.err_message, "");
        return res;
    }
    if (n <= 3) {
        res.value = 1;
        res.is_error = false;
        strcpy(res.err_message, "");
        return res;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        res.value = 0;
        res.is_error = false;
        strcpy(res.err_message, "");
        return res;
    }
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            res.value = 0;
            res.is_error = false;
            strcpy(res.err_message, "");
            return res;
        }
    }
    res.value = 1;
    res.is_error = false;
    strcpy(res.err_message, "");
    return res;
}

// ==================== Rounding and Conversion ====================

CalculationResult scientific_floor(double x) {
    CalculationResult res = { floor(x), false, "" };
    return res;
}

CalculationResult scientific_ceil(double x) {
    CalculationResult res = { ceil(x), false, "" };
    return res;
}

CalculationResult scientific_round(double x) {
    CalculationResult res = { round(x), false, "" };
    return res;
}

CalculationResult scientific_deg2rad(double deg) {
    CalculationResult res = { deg * (M_PI / 180.0), false, "" };
    return res;
}

CalculationResult scientific_rad2deg(double rad) {
    CalculationResult res = { rad * (180.0 / M_PI), false, "" };
    return res;
}

CalculationResult scientific_rand(void) {
    CalculationResult res = { (double)rand() / (double)RAND_MAX, false, "" };
    return res;
}
