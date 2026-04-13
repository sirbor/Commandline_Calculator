#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// CONCEPT: Queue - FIFO data structure (Day 26)

typedef struct QueueNode {
    double data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

Queue* queue_create(void);
void queue_enqueue(Queue *q, double data);
double queue_dequeue(Queue *q);
double queue_peek(Queue *q);
bool queue_is_empty(Queue *q);
int queue_size(Queue *q);
void queue_free(Queue *q);

#endif // QUEUE_H
