#ifndef QUEUE_H
#define QUEUE_H

#include "customer.h"

// Queue node
typedef struct QueueNode {
    Customer cust;
    struct QueueNode *next;
} QueueNode;

// Queue structure
typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

// Function declarations
Queue* createQueue();
int isQueueEmpty(Queue *q);
void enqueue(Queue *q, Customer cust);
Customer dequeue(Queue *q);
Customer peekQueue(Queue *q);
void freeQueue(Queue *q);

#endif
