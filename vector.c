#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Define vector and matrix operations


/**
 * @param   max         - Maximum number of resources
 * @param   allocation  - Allocated number of resource
 * 
 * @return  1 if it passes all sanity checks, 0 if there is an error (-) or if allocation > max
*/
int getNeedMatrix(int** max, int** allocation) {
    for (int i=0; i<num_threads; i++) {
        for (int j=0; j<num_resources; j++) {
            if (allocation[i][j] <= max[i][j]) {
                need[i][j] = max[i][j] - allocation[i][j];
            } else if (allocation[i][j] > max[i][j]) {
                int difference = max[i][j] - allocation[i][j];
                printf("Integrity test failed: allocated resources exceed demand for Thread %d\n", i);
                printf("Need %d instances of resource %d\n", difference, j);
                return 0;
            } 
            
        }
    }
    return 1;
}


/**
 * @param   needRow     - Thread that needs to be checked if it can finish
 * @param   work        - The available resources
 * 
 * @return  1 if the condition is satisfied, 0 otherwise
*/
int compareRow(int* needRow, int* work) {
    // Only 1 condition needs to fail for the schedule to not work
    for (int i=0; i<num_resources; i++) {
        // If needed resources > what is available, fail
        if (needRow[i] > work[i]) {
            return 0;
        }
    }

    // Otherwise, everything is good to go
    return 1;
}

