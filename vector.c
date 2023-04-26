#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Define vector and matrix operations


int getNeedMatrix() {
    for (int i=0; i<num_threads; i++) {
        for (int j=0; j<num_resources; j++) {
            if (allocation[i][j] <= max[i][j]) {
                need[i][j] = max[i][j] - allocation[i][j];
            } else {
                int difference = max[i][j] - allocation[i][j];
                printf("Integrity test failed: allocated resources exceed demand for Thread %d\n", i);
                printf("Need %d instances of resource %d\n", difference, j);
                return 0;
            }
        }
    }
    return 1;
}


int compareRow(int *rowOfNeed, int *work, int num_resources) {
    for (int j = 0; j < num_resources; j++) {
        if (rowOfNeed[j] > work[j]) {
            return 0;
        }
    }
    return 1;
}
