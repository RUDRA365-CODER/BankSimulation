#ifndef QUEUE_H
#define QUEUE_H

#include "customer.h"

typedef struct Node {
    Customer customer;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

Queue* createQueue();
void enqueue(Queue *q, Customer c);
Customer dequeue(Queue *q);
int isEmpty(Queue *q);

#endif
