#ifndef TELLER_H
#define TELLER_H

typedef struct {
    int id;
    double availableTime;
    double totalServiceTime;
} Teller;

Teller* createTellers(int num);

#endif
