#include "data_structs/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// CONCEPT: malloc() for dynamic memory allocation (Day 13)
Node* create_node(double data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Failed to allocate memory for node");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// CONCEPT: Double pointers to modify head of list (Day 22 concept)
void append_node(Node **head, double data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) return;
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    // CONCEPT: Pointer traversal (Day 11)
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// CONCEPT: Recursion and memory cleanup (Day 14)
void free_list(Node *head) {
    if (head == NULL) return;
    free_list(head->next);
    free(head);
}

double get_last_value(Node *head) {
    if (head == NULL) return 0.0;
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}
