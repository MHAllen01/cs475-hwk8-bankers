#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here

int isSafe(int *availableMat, int **allocMat, int **needMat) {
    // Set the work array = to the available array
    int work[num_resources];
    for (int i = 0; i < num_resources; i++) {
        work[i] = availableMat[i];
    }

    // Array of threads that have finished their job
    int finish[num_threads];
    for (int i=0; i<num_threads; i++) {
        finish[i] = 0;
    }

    int i = 0;
    while (finish[i] == 0 && compareRow(needMat[i], work, num_resources) == 1) {
        for (int j=0; j<num_resources; j++) {
            work[j] += allocMat[i][j];
        }
        finish[i] = 1;
        i++;
    }
    
    int returnVal = 0;
    for (int i=0; i<num_threads; i++) {
        if (finish[i] == 1) {
            returnVal++;
        } else {
            returnVal--;
        }
    }

    if (returnVal == num_threads) {
        return 1;
    } else {
        return 0;
    }
}