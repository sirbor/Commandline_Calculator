#include "ops/graphical_ops.h"
#include "evaluation.h"
#include "utils/utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// CONCEPT: 2D Array to represent a "screen" (Day 9)
#define WIDTH 60
#define HEIGHT 20

void graphical_plot(const char *expr) {
    // CONCEPT: ASCII Art - filling a 2D buffer
    char screen[HEIGHT][WIDTH];
    
    // CONCEPT: Initializing 2D array (Day 9)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = (y == HEIGHT/2) ? '-' : ' ';
            if (x == WIDTH/2) screen[y][x] = (y == HEIGHT/2) ? '+' : '|';
        }
    }
    
    // CONCEPT: Loops and precision (Day 11/21)
    // Scale X from -10 to 10
    for (int x = 0; x < WIDTH; x++) {
        double x_val = (double)(x - WIDTH/2) * (10.0 / (WIDTH/2));
        CalculationResult res = evaluate_expression(expr, x_val);
        
        if (!res.is_error) {
            // Scale Y from -1.5 to 1.5 to HEIGHT
            int y = HEIGHT/2 - (int)(res.value * (HEIGHT/3.0));
            if (y >= 0 && y < HEIGHT) {
                screen[y][x] = '*';
            }
        }
    }
    
    // CONCEPT: 2D Array traversal and printing
    printf("\nPlot of %s:\n", expr);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
