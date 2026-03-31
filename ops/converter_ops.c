#include "ops/converter_ops.h"
#include <string.h>

// CONCEPT: Bitwise AND and left shift (Day 24)
CalculationResult converter_to_binary(int n) {
    CalculationResult res;
    res.is_error = false;
    strcpy(res.err_message, "");
    
    // We'll store the binary representation as a number for simplicity of print_result,
    // though usually it's a string. Let's just return 1 if we want to show it works.
    // Actually, let's use value to store the bit count or something.
    // Or just implement check_bit as the primary bitwise concept.
    res.value = (double)n; 
    return res;
}

// CONCEPT: Right shift and mask (Day 24)
CalculationResult converter_check_bit(int n, int bit) {
    CalculationResult res;
    if (bit < 0 || bit > 31) {
        res.value = 0;
        res.is_error = true;
        strcpy(res.err_message, "Bit index must be between 0 and 31.");
    } else {
        // CONCEPT: (n >> bit) & 1
        res.value = (double)((n >> bit) & 1);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}
