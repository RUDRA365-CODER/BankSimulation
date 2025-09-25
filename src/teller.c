#include <stdlib.h>
#include "teller.h"

Teller* createTellers(int num) {
    Teller* tellers = (Teller*)malloc(num * sizeof(Teller));
    for (int i = 0; i < num; i++) {
        tellers[i].id = i;
        tellers[i].availableTime = 0;
        tellers[i].totalServiceTime = 0;
    }
    return tellers;
}
