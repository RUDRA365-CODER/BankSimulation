#include <stdlib.h>
#include "event.h"

EventNode* insertEvent(EventNode* head, Event ev) {
    EventNode* newNode = (EventNode*)malloc(sizeof(EventNode));
    newNode->event = ev;
    newNode->next = NULL;

    if (!head || ev.time < head->event.time) {
        newNode->next = head;
        return newNode;
    }

    EventNode* temp = head;
    while (temp->next && temp->next->event.time < ev.time) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

Event popEvent(EventNode** head) {
    Event event = (*head)->event;
    EventNode* temp = *head;
    *head = (*head)->next;
    free(temp);
    return event;
}
