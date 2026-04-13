#include "ops/graphical_ops.h"
#include "evaluation.h"
#include "utils/utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

// CONCEPT: 2D Array to represent a "screen" (Day 9)
#define WIDTH 65
#define HEIGHT 20

void graphical_plot(const char *expr) {
    // CONCEPT: ASCII Art - filling a 2D buffer
    char screen[HEIGHT][WIDTH];
    int is_point[HEIGHT][WIDTH];
    double values[WIDTH];
    double y_min = DBL_MAX, y_max = -DBL_MAX;
    
    // Initialize is_point array
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            is_point[y][x] = 0;
        }
    }
    
    // First pass: compute all values and find min/max for auto-scaling
    for (int x = 0; x < WIDTH; x++) {
        double x_val = (double)(x - WIDTH/2) * (10.0 / (WIDTH/2));
        CalculationResult res = evaluate_expression(expr, x_val);
        
        if (!res.is_error && !isnan(res.value) && !isinf(res.value)) {
            values[x] = res.value;
            if (res.value < y_min) y_min = res.value;
            if (res.value > y_max) y_max = res.value;
        } else {
            values[x] = NAN;
        }
    }
    
    // Handle edge cases
    if (y_min == DBL_MAX || y_max == -DBL_MAX) {
        log_error("Could not evaluate expression");
        return;
    }
    
    // Store original range for display
    double display_y_min = y_min;
    double display_y_max = y_max;
    
    // Add some padding to y range
    double y_range = y_max - y_min;
    if (y_range < 0.001) {
        y_min -= 1.0;
        y_max += 1.0;
        y_range = 2.0;
    } else {
        y_min -= y_range * 0.1;
        y_max += y_range * 0.1;
        y_range = y_max - y_min;
    }
    
    // Find where y=0 line should be
    int zero_row = -1;
    if (y_min <= 0 && y_max >= 0) {
        zero_row = (int)((y_max / y_range) * (HEIGHT - 1));
    }
    
    // CONCEPT: Initializing 2D array (Day 9)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == zero_row) {
                screen[y][x] = '-';
            } else {
                screen[y][x] = ' ';
            }
            if (x == WIDTH/2) {
                screen[y][x] = (y == zero_row) ? '+' : '|';
            }
        }
    }
    
    // Second pass: plot the values with auto-scaling
    for (int x = 0; x < WIDTH; x++) {
        if (!isnan(values[x])) {
            double normalized = (y_max - values[x]) / y_range;
            int y = (int)(normalized * (HEIGHT - 1));
            if (y >= 0 && y < HEIGHT) {
                screen[y][x] = '*';
                is_point[y][x] = 1;
            }
        }
    }
    
    // Print modern header
    printf("\n");
    printf("    %s╭─────────────────────────────────────────────────────────────────────╮%s\n", COLOR_TEAL, COLOR_RESET);
    printf("    %s│%s  %s%s%s f(x) = %s%-55s%s  %s│%s\n", 
           COLOR_TEAL, COLOR_RESET, 
           COLOR_PURPLE, SYM_WAVE, COLOR_RESET,
           COLOR_GOLD, expr, COLOR_RESET,
           COLOR_TEAL, COLOR_RESET);
    printf("    %s├─────────────────────────────────────────────────────────────────────┤%s\n", COLOR_TEAL, COLOR_RESET);
    
    // Print Y-axis max label
    printf("    %s│%s %s%8.2f%s %s┬%s                                                          %s│%s\n",
           COLOR_TEAL, COLOR_RESET,
           COLOR_MINT, display_y_max, COLOR_RESET,
           STYLE_DIM, COLOR_RESET,
           COLOR_TEAL, COLOR_RESET);
    
    // CONCEPT: 2D Array traversal with colored output
    for (int y = 0; y < HEIGHT; y++) {
        printf("    %s│%s %8s %s│%s", COLOR_TEAL, COLOR_RESET, "", STYLE_DIM, COLOR_RESET);
        for (int x = 0; x < WIDTH; x++) {
            if (is_point[y][x]) {
                printf("%s●%s", COLOR_LIME, COLOR_RESET);
            } else if (screen[y][x] == '|') {
                printf("%s│%s", STYLE_DIM, COLOR_RESET);
            } else if (screen[y][x] == '-') {
                printf("%s─%s", STYLE_DIM, COLOR_RESET);
            } else if (screen[y][x] == '+') {
                printf("%s┼%s", COLOR_GOLD, COLOR_RESET);
            } else {
                printf(" ");
            }
        }
        printf(" %s│%s\n", COLOR_TEAL, COLOR_RESET);
    }
    
    // Print Y-axis min label and X range
    printf("    %s│%s %s%8.2f%s %s┴%s                                                          %s│%s\n",
           COLOR_TEAL, COLOR_RESET,
           COLOR_CORAL, display_y_min, COLOR_RESET,
           STYLE_DIM, COLOR_RESET,
           COLOR_TEAL, COLOR_RESET);
    printf("    %s├─────────────────────────────────────────────────────────────────────┤%s\n", COLOR_TEAL, COLOR_RESET);
    printf("    %s│%s          %s-10%s %s──────────────────── x ────────────────────%s %s+10%s        %s│%s\n",
           COLOR_TEAL, COLOR_RESET,
           COLOR_SKY, COLOR_RESET,
           STYLE_DIM, COLOR_RESET,
           COLOR_SKY, COLOR_RESET,
           COLOR_TEAL, COLOR_RESET);
    printf("    %s╰─────────────────────────────────────────────────────────────────────╯%s\n\n", COLOR_TEAL, COLOR_RESET);
}
