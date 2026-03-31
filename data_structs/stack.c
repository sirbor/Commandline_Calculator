#include "data_structs/stack.h"
#include <stdlib.h>
#include <stdio.h>

void stack_push(Stack *s, double val) {
    StackNode *new_node = malloc(sizeof(StackNode));
    if (!new_node) return;
    new_node->data = val;
    new_node->next = s->top;
    s->top = new_node;
}

double stack_pop(Stack *s) {
    if (s->top == NULL) return 0.0;
    StackNode *temp = s->top;
    double val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}

void stack_free(Stack *s) {
    while (s->top != NULL) {
        stack_pop(s);
    }
}
