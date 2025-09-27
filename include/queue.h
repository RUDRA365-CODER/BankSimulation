#ifndef QUEUE_H
#define QUEUE_H

#include "customer.h"

typedef struct Node {
    Customer customer;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

Queue* createQueue();
void enqueue(Queue *q, Customer cust);
Customer dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void freeQueue(Queue *q);

#endif
