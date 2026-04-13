#include "evaluation.h"
#include "ops/scientific_ops.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// CONCEPT: Recursive descent parser for mathematical expressions

#define CONST_PI 3.14159265358979323846
#define CONST_E 2.71828182845904523536

typedef struct {
    bool has_error;
    char message[MAX_ERR_LEN];
} EvalState;

// Forward declarations for recursive descent
static double parse_expression(const char **s, double x, EvalState *state);
static double parse_term(const char **s, double x, EvalState *state);
static double parse_factor(const char **s, double x, EvalState *state);
static double parse_power(const char **s, double x, EvalState *state);
static double parse_primary(const char **s, double x, EvalState *state);

static void set_error(EvalState *state, const char *message) {
    if (!state->has_error) {
        state->has_error = true;
        snprintf(state->message, sizeof(state->message), "%s", message);
    }
}

// Skip whitespace
static void skip_whitespace(const char **s) {
    while (**s && isspace((unsigned char)**s)) (*s)++;
}

// Parse a number
static double parse_number(const char **s) {
    char *end;
    double val = strtod(*s, &end);
    *s = end;
    return val;
}

// Check if current position starts with a string
static int match(const char **s, const char *str) {
    size_t len = strlen(str);
    if (strncmp(*s, str, len) == 0) {
        *s += len;
        return 1;
    }
    return 0;
}

// Parse primary: numbers, x, functions, parentheses
static double parse_primary(const char **s, double x, EvalState *state) {
    skip_whitespace(s);
    if (state->has_error) return 0.0;
    
    // Parentheses
    if (**s == '(') {
        (*s)++;
        double val = parse_expression(s, x, state);
        skip_whitespace(s);
        if (**s == ')') {
            (*s)++;
        } else {
            set_error(state, "Missing closing ')'.");
        }
        return val;
    }
    
    // Variable x
    if (**s == 'x' && !isalpha((unsigned char)(*s)[1])) {
        (*s)++;
        return x;
    }
    
    // Mathematical constants - must check longer strings first
    if (match(s, "pi")) return CONST_PI;
    
    // Functions - check exp BEFORE checking 'e' constant
    if (match(s, "exp(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after exp().");
        return exp(val);
    }
    
    // Now check 'e' constant (after exp)
    if (**s == 'e' && !isalpha((unsigned char)(*s)[1])) {
        (*s)++;
        return CONST_E;
    }
    
    // Other functions
    if (match(s, "sin(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after sin().");
        return sin(val);
    }
    if (match(s, "cos(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after cos().");
        return cos(val);
    }
    if (match(s, "tan(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after tan().");
        return tan(val);
    }
    if (match(s, "sqrt(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after sqrt().");
        return sqrt(val);
    }
    if (match(s, "abs(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after abs().");
        return fabs(val);
    }
    if (match(s, "log10(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after log10().");
        return log10(val);
    }
    if (match(s, "log(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after log().");
        return log(val);
    }
    if (match(s, "asin(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after asin().");
        return asin(val);
    }
    if (match(s, "acos(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after acos().");
        return acos(val);
    }
    if (match(s, "atan(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after atan().");
        return atan(val);
    }
    if (match(s, "floor(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after floor().");
        return floor(val);
    }
    if (match(s, "ceil(")) {
        double val = parse_expression(s, x, state);
        if (**s == ')') (*s)++;
        else set_error(state, "Missing ')' after ceil().");
        return ceil(val);
    }
    
    // Number
    if (isdigit((unsigned char)**s) || **s == '.') {
        return parse_number(s);
    }
    
    if (**s == '\0') set_error(state, "Unexpected end of expression.");
    else set_error(state, "Unexpected token in expression.");
    return 0.0;
}

// Parse power: x^2, 2^x - unary is handled at primary level
static double parse_power(const char **s, double x, EvalState *state) {
    skip_whitespace(s);
    int negate = 0;
    
    // Handle leading minus for the base
    if (**s == '-') {
        (*s)++;
        negate = 1;
    } else if (**s == '+') {
        (*s)++;
    }
    
    double left = parse_primary(s, x, state);
    if (negate) left = -left;
    if (state->has_error) return 0.0;
    
    skip_whitespace(s);
    if (**s == '^') {
        (*s)++;
        // For power, we need to handle precedence correctly
        // -2^2 should be -(2^2) = -4, not (-2)^2 = 4
        // But (-2)^2 should be 4
        // Since we already applied negate to left, we need to reconsider
        // Actually, in standard math: -x^n = -(x^n)
        // So -2^2 = -(2^2) = -4
        // Let's revert left and handle the negation after
        if (negate) {
            left = -left;  // Revert
            double right = parse_power(s, x, state);
            return -pow(left, right);
        } else {
            double right = parse_power(s, x, state);
            return pow(left, right);
        }
    }
    return left;
}

// Parse factor: x*y, x/y
static double parse_factor(const char **s, double x, EvalState *state) {
    double left = parse_power(s, x, state);
    while (1) {
        skip_whitespace(s);
        if (**s == '*') {
            (*s)++;
            left *= parse_power(s, x, state);
        } else if (**s == '/') {
            (*s)++;
            double right = parse_power(s, x, state);
            if (fabs(right) > 1e-15) left /= right;
            else {
                set_error(state, "Division by zero.");
                return 0.0;
            }
        } else {
            break;
        }
        if (state->has_error) return 0.0;
    }
    return left;
}

// Parse term: x+y, x-y
static double parse_term(const char **s, double x, EvalState *state) {
    double left = parse_factor(s, x, state);
    while (1) {
        skip_whitespace(s);
        if (**s == '+') {
            (*s)++;
            left += parse_factor(s, x, state);
        } else if (**s == '-') {
            (*s)++;
            left -= parse_factor(s, x, state);
        } else {
            break;
        }
        if (state->has_error) return 0.0;
    }
    return left;
}

// Top-level expression parser
static double parse_expression(const char **s, double x, EvalState *state) {
    return parse_term(s, x, state);
}

// CONCEPT: Recursive descent parser for mathematical expressions
CalculationResult evaluate_expression(const char *expr, double x_val) {
    CalculationResult res = {0.0, false, ""};
    EvalState state = {false, ""};
    
    const char *s = expr;
    res.value = parse_expression(&s, x_val, &state);
    skip_whitespace(&s);
    if (!state.has_error && *s != '\0') {
        set_error(&state, "Unexpected trailing tokens in expression.");
    }
    
    // Check for NaN or Inf
    if (state.has_error) {
        res.is_error = true;
        snprintf(res.err_message, sizeof(res.err_message), "%s", state.message);
    } else if (isnan(res.value) || isinf(res.value)) {
        res.is_error = true;
        strcpy(res.err_message, "Math error (NaN or Inf)");
    }
    
    return res;
}
