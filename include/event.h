#ifndef EVENT_H
#define EVENT_H

typedef enum { ARRIVAL, DEPARTURE } EventType;

typedef struct {
    int id;
    EventType type;
    double time;
} Event;

typedef struct EventNode {
    Event event;
    struct EventNode *next;
} EventNode;

EventNode* insertEvent(EventNode* head, Event ev);
Event popEvent(EventNode** head);

#endif
