#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

/**
 * Check:
 * 1. Currently allocated resources don't exceed total number of resources
 * 2. Thread's don't exceed max demands for each resource type
*/
int num_resources;
int num_threads;
int* available;
int** max;
int** allocation;
int** need;

void initMatrices(int num_resources, int num_threads) {
  // Allocate space for the available resources
    available = (int *) malloc(num_resources *sizeof(int));

    // Allocate space for the max resources
    max = (int **) malloc(num_threads * sizeof(int *));
    for (int i=0; i< num_threads; i++) {
      max[i] = (int *) malloc(num_resources *sizeof(int));
    }

    // Allocate space for the allocated resources
    allocation = (int **) malloc(num_threads * sizeof(int *));
    for (int i=0; i< num_threads; i++) {
      allocation[i] = (int *) malloc(num_resources *sizeof(int));
    }

    // Allocate space for the needed resources
    need = (int **) malloc(num_threads * sizeof(int *));
    for (int i=0; i< num_threads; i++) {
      need[i] = (int *) malloc(num_resources *sizeof(int));
    }
    
}

int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures

  // TODO: Run banker's safety algorithm

  // File to open
  FILE *file;
  file = fopen(argv[1], "r");

  if (file != NULL) {
    // File was opened successfully

    // Scan first two lines
    fscanf(file, "%d %d", &num_resources, &num_threads);
    
    initMatrices(num_resources, num_threads);
  
    // Scan the available resources
    for (int i=0; i<num_resources; i++) {
      fscanf(file, "%d", &available[i]);
    }

    

    // Scan the max resources
    for (int i=0; i<num_threads; i++) {
      for (int j=0; j<num_resources; j++) {
        fscanf(file, "%d", &max[i][j]);
      }
    }

    

    // Scan the allocated resources
    for (int i=0; i<num_threads; i++) {
      for (int j=0; j<num_resources; j++) {
        fscanf(file, "%d", &allocation[i][j]);
      }
    }

    if (getNeedMatrix() == 1) {
      if (isSafe(available, allocation, need) == 1) {
        printf("Everything worked\n");
      } else {
        printf("Nope\n");
      }
    }


    

    

    // Close the file
    fclose(file);
  } else {
    printf("whoops\n");
  }
  return 0;
}