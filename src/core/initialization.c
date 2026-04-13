#include "initialization.h"
#include "utils/utils.h"
#include "common.h"
#include <stdio.h>
#include <time.h>

static void print_progress_bar(int step, int total) {
    printf("\r  %s", COLOR_TEAL);
    for (int i = 0; i < total; i++) {
        if (i < step) printf("━");
        else printf("%s━%s", STYLE_DIM, COLOR_TEAL);
    }
    printf("%s ", COLOR_RESET);
    fflush(stdout);
}

static void sleep_milliseconds(long milliseconds) {
    clock_t start = clock();
    double seconds = (double)milliseconds / 1000.0;
    while (((double)(clock() - start) / (double)CLOCKS_PER_SEC) < seconds) {
        // Busy-wait fallback for strict C99 portability.
    }
}

void initialize_calculator(void) {
    printf("\n");
    
    // Quick progress animation
    const char *steps[] = {"Loading modules", "Initializing parser", "Ready"};
    for (int i = 0; i < 3; i++) {
        print_progress_bar(i + 1, 3);
        printf("%s%s%s", STYLE_DIM, steps[i], COLOR_RESET);
        fflush(stdout);
        sleep_milliseconds(80);
    }
    printf("\n\n");
}
