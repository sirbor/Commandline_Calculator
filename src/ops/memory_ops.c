#include "ops/memory_ops.h"
#include "data_structs/bst.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

// CONCEPT: static keyword - visibility restricted to this file
static BSTNode *memory_tree = NULL;

void memory_store(const char *name, double val) {
    bst_insert(&memory_tree, name, val);
}

CalculationResult memory_recall(const char *name) {
    CalculationResult res;
    BSTNode *node = bst_search(memory_tree, name);
    if (node == NULL) {
        res.value = 0.0;
        res.is_error = true;
        snprintf(res.err_message, MAX_ERR_LEN, "Variable '%s' not found.", name);
    } else {
        res.value = node->data;
        res.is_error = false;
        strcpy(res.err_message, "");
    }
    return res;
}

void memory_list(void (*callback)(const char*, double)) {
    bst_inorder(memory_tree, callback);
}

void memory_cleanup(void) {
    bst_free(memory_tree);
    memory_tree = NULL;
}
