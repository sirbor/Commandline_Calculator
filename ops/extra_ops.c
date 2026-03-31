#include "ops/extra_ops.h"
#include <stdio.h>
#include <string.h>

// CONCEPT: fopen, fprintf, fclose (Day 18)
CalculationResult extra_save_result(double val, const char *filename) {
    CalculationResult res = {0.0, false, ""};
    
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        res.is_error = true;
        strcpy(res.err_message, "Could not open file for writing.");
        return res;
    }
    
    fprintf(f, "Result: %.2f\n", val);
    fclose(f);
    
    res.value = val;
    return res;
}
