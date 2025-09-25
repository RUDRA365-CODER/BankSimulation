#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "event.h"
#include "queue.h"
#include "teller.h"
#include "customer.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s #customers #tellers simulationTime averageServiceTime\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int numCustomers = atoi(argv[1]);
    int numTellers = atoi(argv[2]);
    double simulationTime = atof(argv[3]);
    double avgServiceTime = atof(argv[4]);

    EventNode *eventQueue = NULL;
    Queue *customerQueue = createQueue();
    Teller *tellers = createTellers(numTellers);

    double *customerTimes = malloc(sizeof(double) * numCustomers); 
    double totalTimeInBank = 0;
    double totalWaitTime = 0;
    double maxWaitTime = 0;
    int totalServed = 0;

    
    for (int i = 0; i < numCustomers; i++) {
        double arrTime = simulationTime * rand() / (float)RAND_MAX;
        double servTime = 2 * avgServiceTime * rand() / (float)RAND_MAX;

        Event ev = { i, ARRIVAL, arrTime };
        eventQueue = insertEvent(eventQueue, ev);

        Customer cust = { i, arrTime, servTime, 0 };
        enqueue(customerQueue, cust);
    }

    
    while (eventQueue) {
        Event event = popEvent(&eventQueue);

        if (event.type == ARRIVAL) {
            for (int i = 0; i < numTellers; i++) {
                if (tellers[i].availableTime <= event.time) {
                    Customer cust = dequeue(customerQueue);
                    cust.startServiceTime = event.time;

                    double waitTime = cust.startServiceTime - cust.arrivalTime;
                    totalWaitTime += waitTime;
                    if (waitTime > maxWaitTime) maxWaitTime = waitTime;

                    double totalCustomerTime = waitTime + cust.serviceTime;
                    customerTimes[cust.id] = totalCustomerTime;

                    totalTimeInBank += totalCustomerTime;
                    tellers[i].totalServiceTime += cust.serviceTime;
                    tellers[i].availableTime = event.time + cust.serviceTime;

                    Event dep = { cust.id, DEPARTURE, tellers[i].availableTime };
                    eventQueue = insertEvent(eventQueue, dep);

                    totalServed++;
                    break;
                }
            }
        }
    }

    
    double averageTime = totalTimeInBank / totalServed;

    
    double extraAverageTime = totalWaitTime / totalServed;

    
    double varianceSum = 0;
    for (int i = 0; i < totalServed; i++) {
        varianceSum += pow(customerTimes[i] - averageTime, 2);
    }
    double stdDeviation = sqrt(varianceSum / totalServed);

    
    printf("Total customers served: %d\n", totalServed);
    printf("Average time in bank: %.2f minutes\n", averageTime);
    printf("Extra average wait time: %.2f minutes\n", extraAverageTime);
    printf("Maximum wait time: %.2f minutes\n", maxWaitTime);
    printf("Standard deviation of time: %.2f minutes\n", stdDeviation);

    free(customerTimes);
    FILE *fp = fopen("test/results.txt", "a"); 

if (fp != NULL) {
    fprintf(fp, "%d %.2f\n", numTellers, totalTimeInBank / totalServed);
    fclose(fp);
} else {
    printf("Error: Unable to write results file.\n");
}

    free(tellers);
    return 0;
}
