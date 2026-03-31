#ifndef STACK_H
#define STACK_H

#include "common.h"

// CONCEPT: LIFO Stack data structure (Day 16/26)
typedef struct StackNode {
    double data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

void stack_push(Stack *s, double val);
double stack_pop(Stack *s);
void stack_free(Stack *s);

#endif // STACK_H
