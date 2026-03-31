#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

// CONCEPT: Self-referential structures (Day 11)
typedef struct Node {
    double data;
    struct Node *next;
} Node;

// CONCEPT: Pointer-based dynamic data structure
Node* create_node(double data);
void append_node(Node **head, double data);
void free_list(Node *head);
double get_last_value(Node *head);

#endif // LINKED_LIST_H
