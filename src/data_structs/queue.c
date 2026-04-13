#include "data_structs/queue.h"
#include <stdlib.h>
#include <stdio.h>

// CONCEPT: Queue creation with front/rear pointers
Queue* queue_create(void) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Failed to allocate queue");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

// CONCEPT: FIFO - enqueue at rear
void queue_enqueue(Queue *q, double data) {
    if (q == NULL) return;
    
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL) {
        perror("Failed to allocate queue node");
        return;
    }
    node->data = data;
    node->next = NULL;
    
    if (q->rear == NULL) {
        // Empty queue
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
    q->size++;
}

// CONCEPT: FIFO - dequeue from front
double queue_dequeue(Queue *q) {
    if (q == NULL || q->front == NULL) {
        return 0.0;
    }
    
    QueueNode *temp = q->front;
    double data = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return data;
}

double queue_peek(Queue *q) {
    if (q == NULL || q->front == NULL) {
        return 0.0;
    }
    return q->front->data;
}

bool queue_is_empty(Queue *q) {
    return (q == NULL || q->front == NULL);
}

int queue_size(Queue *q) {
    return (q == NULL) ? 0 : q->size;
}

// CONCEPT: Proper cleanup - free all nodes then queue struct
void queue_free(Queue *q) {
    if (q == NULL) return;
    
    QueueNode *current = q->front;
    while (current != NULL) {
        QueueNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
}
