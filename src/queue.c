#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(Queue *q, Customer cust) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->customer = cust;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = temp;
        q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

Customer dequeue(Queue *q) {
    Customer cust = { -1, 0, 0, 0 }; // default invalid customer
    if (q->front == NULL) return cust;

    Node *temp = q->front;
    cust = temp->customer;
    q->front = q->front->next;

    if (q->front == NULL) q->rear = NULL;

    free(temp);
    return cust;
}

int isQueueEmpty(Queue *q) {
    return (q->front == NULL);
}

void freeQueue(Queue *q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}
