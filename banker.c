#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here

/**
 * @param   available       - The available amount of resources
 * @param   allocation      - The number of allocated resources
 * @param   need            - The number of needed resources
 * 
 * @return  1 if is safe path, 0 otherwise
*/
int isSafe(int* available, int** allocation, int** need) {
    // "CLONE" the available resources -- leave available untouched
    // (Copy the array into another array)
    int work[num_resources];
    for (int i=0; i<num_resources; i++) {
        work[i] = available[i];
    }

    // Create an array of threads that have finished their job
    // 0 is job not finished -- Initalize to 0
    // 1 is job finished
    int finish[num_threads];
    for (int i=0; i<num_threads; i++) {
        finish[i] = 0;
    }

    // While there is an unfinished thread
    // and the row of need is <= work (work is a row too)
    // (row of need == thread section)
    int counter = 0; // Incremental counter for while loop
    while(finish[counter] == 0 && compareRow(need[counter], work) == 1) {
        // Thread i can finish execution
        // Reclaim its allocated resources to check for another thread
        for (int i=0; i<num_threads; i++) {
            for (int j=0; j<num_resources; j++) {
                work[j] += allocation[i][j];
            }
        }

        // Set the thread to being complete
        finish[counter] = 1;

        // Increment the counter
        counter++;
    }

    /*  
        Check the finish array
        If any thread is at 0, then the schedule is unsafe => return 0
        Otherwise, return 1
    */

    for (int i=0; i<num_threads; i++) {
        if (finish[i] != 1) {
            return 0;
        }
    }

    return 1;
}