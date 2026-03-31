#include "ops/memory_ops.h"
#include "data_structs/linked_list.h"
#include <stddef.h>
#include <string.h>

// CONCEPT: static keyword - visibility restricted to this file
static Node *memory_list = NULL;

void memory_store(double val) {
    append_node(&memory_list, val);
}

CalculationResult memory_recall() {
    CalculationResult res;
    if (memory_list == NULL) {
        res.value = 0.0;
        res.is_error = true;
        strcpy(res.err_message, "Memory is empty.");
    } else {
        res.value = get_last_value(memory_list);
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

void memory_cleanup() {
    free_list(memory_list);
    memory_list = NULL;
}
