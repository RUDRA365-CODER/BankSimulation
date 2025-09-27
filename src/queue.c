#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Create new queue
Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// Check if queue is empty
int isQueueEmpty(Queue *q) {
    return (q->size == 0);
}

// Add customer to rear
void enqueue(Queue *q, Customer cust) {
    QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->cust = cust;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->size++;
}

// Remove customer from front
Customer dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        Customer empty = { -1, 0, 0, 0 }; // return invalid customer
        return empty;
    }
    QueueNode *temp = q->front;
    Customer cust = temp->cust;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    q->size--;
    return cust;
}

// Peek front customer without removing
Customer peekQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        Customer empty = { -1, 0, 0, 0 };
        return empty;
    }
    return q->front->cust;
}

// Free memory
void freeQueue(Queue *q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}
