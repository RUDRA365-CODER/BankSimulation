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

    // Create queues
    Queue *singleQueue = createQueue();
    Queue **separateQueues = (Queue**)malloc(numTellers * sizeof(Queue*));
    for (int i = 0; i < numTellers; i++) {
        separateQueues[i] = createQueue();
    }

    Teller *tellers = createTellers(numTellers);

    double *customerTimes = malloc(sizeof(double) * numCustomers);
    double totalTimeInBankSingle = 0, totalWaitTimeSingle = 0, maxWaitSingle = 0;
    double totalTimeInBankMulti = 0, totalWaitTimeMulti = 0, maxWaitMulti = 0;
    int totalServedSingle = 0, totalServedMulti = 0;

    // Generate customers
    Customer *customers = malloc(sizeof(Customer) * numCustomers);
    for (int i = 0; i < numCustomers; i++) {
        double arrTime = simulationTime * rand() / (float)RAND_MAX;
        double servTime = 2 * avgServiceTime * rand() / (float)RAND_MAX;
        customers[i] = (Customer){ i, arrTime, servTime, 0 };
        enqueue(singleQueue, customers[i]);

        // choose random queue initially for separate mode
        int qIndex = rand() % numTellers;
        enqueue(separateQueues[qIndex], customers[i]);
    }

    // ---- Simulation for single queue ----
    for (int i = 0; i < numTellers; i++) tellers[i].availableTime = 0;
    while (!isQueueEmpty(singleQueue)) {
        Customer cust = dequeue(singleQueue);

        // Find earliest available teller
        int chosen = 0;
        double minAvail = tellers[0].availableTime;
        for (int i = 1; i < numTellers; i++) {
            if (tellers[i].availableTime < minAvail) {
                minAvail = tellers[i].availableTime;
                chosen = i;
            }
        }

        double startTime = fmax(cust.arrivalTime, tellers[chosen].availableTime);
        cust.startServiceTime = startTime;

        double waitTime = startTime - cust.arrivalTime;
        if (waitTime < 0) waitTime = 0; // clamp

        totalWaitTimeSingle += waitTime;
        if (waitTime > maxWaitSingle) maxWaitSingle = waitTime;

        double totalCustTime = waitTime + cust.serviceTime;
        totalTimeInBankSingle += totalCustTime;
        customerTimes[cust.id] = totalCustTime;

        tellers[chosen].availableTime = cust.startServiceTime + cust.serviceTime;
        totalServedSingle++;
    }

    // ---- Simulation for separate queues ----
    for (int i = 0; i < numTellers; i++) tellers[i].availableTime = 0;
    int customersLeft = numCustomers;
    while (customersLeft > 0) {
        for (int i = 0; i < numTellers; i++) {
            if (!isQueueEmpty(separateQueues[i])) {
                Customer cust = dequeue(separateQueues[i]);

                double startTime = fmax(cust.arrivalTime, tellers[i].availableTime);
                cust.startServiceTime = startTime;

                double waitTime = startTime - cust.arrivalTime;
                if (waitTime < 0) waitTime = 0;

                totalWaitTimeMulti += waitTime;
                if (waitTime > maxWaitMulti) maxWaitMulti = waitTime;

                double totalCustTime = waitTime + cust.serviceTime;
                totalTimeInBankMulti += totalCustTime;
                customerTimes[cust.id] = totalCustTime;

                tellers[i].availableTime = cust.startServiceTime + cust.serviceTime;
                totalServedMulti++;
                customersLeft--;
            }
        }
    }

    // ---- Stats ----
    double avgTimeSingle = totalTimeInBankSingle / totalServedSingle;
    double avgWaitSingle = totalWaitTimeSingle / totalServedSingle;

    double avgTimeMulti = totalTimeInBankMulti / totalServedMulti;
    double avgWaitMulti = totalWaitTimeMulti / totalServedMulti;

    printf("\n--- Single Queue Mode ---\n");
    printf("Total customers served: %d\n", totalServedSingle);
    printf("Average time in bank: %.2f minutes\n", avgTimeSingle);
    printf("Average wait time: %.2f minutes\n", avgWaitSingle);
    printf("Maximum wait time: %.2f minutes\n", maxWaitSingle);

    printf("\n--- Separate Queue Mode ---\n");
    printf("Total customers served: %d\n", totalServedMulti);
    printf("Average time in bank: %.2f minutes\n", avgTimeMulti);
    printf("Average wait time: %.2f minutes\n", avgWaitMulti);
    printf("Maximum wait time: %.2f minutes\n", maxWaitMulti);

    // Cleanup
    free(customerTimes);
    free(customers);
    free(tellers);
    freeQueue(singleQueue);
    for (int i = 0; i < numTellers; i++) {
        freeQueue(separateQueues[i]);
    }
    free(separateQueues);

    return 0;
}
