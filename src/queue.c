#include <stdlib.h>
#include "queue.h"

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, Customer c) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->customer = c;
    temp->next = NULL;

    if (!q->rear) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

Customer dequeue(Queue *q) {
    Customer c = {0};
    if (!q->front) return c;

    Node* temp = q->front;
    c = temp->customer;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return c;
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}
