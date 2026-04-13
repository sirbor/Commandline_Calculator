#include "ops/history_ops.h"
#include "data_structs/queue.h"
#include <stdio.h>
#include <stdlib.h>

// CONCEPT: Static pointer for singleton-like queue management
static Queue *history_queue = NULL;
#define MAX_HISTORY 10

void history_add(double val) {
    if (history_queue == NULL) {
        history_queue = queue_create();
    }
    
    if (queue_size(history_queue) >= MAX_HISTORY) {
        queue_dequeue(history_queue);
    }
    
    queue_enqueue(history_queue, val);
}

static void print_history_node(QueueNode *node, int count) {
    if (node == NULL) return;
    print_history_node(node->next, count - 1);
    printf("  %2d. %s%g%s\n", count, COLOR_GOLD, node->data, COLOR_RESET);
}

void history_show(void) {
    if (history_queue == NULL || queue_is_empty(history_queue)) {
        printf("  %s(History is empty)%s\n", STYLE_DIM, COLOR_RESET);
        return;
    }
    
    printf("\n  ╭── CALCULATOR HISTORY ───╮\n");
    print_history_node(history_queue->front, queue_size(history_queue));
    printf("  ╰─────────────────────────╯\n\n");
}

void history_clear(void) {
    if (history_queue != NULL) {
        queue_free(history_queue);
        history_queue = NULL;
    }
}

CalculationResult history_last(void) {
    CalculationResult res = {0.0, false, ""};
    if (history_queue == NULL || queue_is_empty(history_queue)) {
        res.is_error = true;
        snprintf(res.err_message, MAX_ERR_LEN, "History is empty.");
        return res;
    }

    res.value = history_queue->rear->data;
    return res;
}

void history_cleanup(void) {
    history_clear();
}
