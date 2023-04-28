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
int* path;
int* finish;


/**
 * Initalizes the matrices for memory allocation
 * 
 * @param   num_resources   - The number of resources in the system
 * @param   num_threads     - The number of threads in the system
*/
void initMatrices(int num_resources, int num_threads) {

    // Allocate space for the available resources and initalize to 0
    available = (int *) malloc(num_resources * sizeof(int));

    // Allocate space for the path of finished threads
    path = (int *) malloc(num_threads * sizeof(int));
    for (int i=0; i<num_resources; i++) {
      available[i] = 0;
    }

    // Allocate space for the finished threads and initalize to 0
    finish = (int *) malloc(num_threads * sizeof(int));
    for (int i=0; i<num_threads; i++) {
      finish[i] = 0;
    }

    // Allocate space for the max resources and initalize to 0
    max = (int **) malloc(num_threads * sizeof(int *));
    for (int i=0; i< num_threads; i++) {
      max[i] = (int *) malloc(num_resources * sizeof(int));
      for (int j=0; j<num_resources; j++) {
            max[i][j] = 0;
        }
    }

    // Allocate space for the allocated resources and initalize to 0
    allocation = (int **) malloc(num_threads * sizeof(int *));
    for (int i=0; i< num_threads; i++) {
      allocation[i] = (int *) malloc(num_resources * sizeof(int));
      for (int j=0; j<num_resources; j++) {
            allocation[i][j] = 0;
        }
    }

    // Allocate space for the needed resources and initalize to 0
    need = (int **) malloc(num_threads * sizeof(int *));
    for (int i=0; i< num_threads; i++) {
      need[i] = (int *) malloc(num_resources * sizeof(int));
      for (int j=0; j<num_resources; j++) {
            need[i][j] = 0;
        }
    }
    
}

/**
 * Frees up the allocated matrices
*/
void freeup() {
  // Nullify everything
  available = NULL;
  path = NULL;
  finish = NULL;
  for (int i=0; i<num_threads; i++) {
      max[i] = NULL;
      allocation[i] = NULL;
      need[i] = NULL;
  }

  // Free everything
  free(available);
  free(path);
  free(finish);
  free(max);
  free(allocation);
  free(need);
}

int main(int argc, char *argv[]) {
  // File to open
  FILE *file;
  file = fopen(argv[1], "r");

  if (file != NULL && argc == 2) {
    // File was opened successfully

    // Scan first two lines
    fscanf(file, "%d %d", &num_resources, &num_threads);
    
    // Initalize the matrices
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

    // Calculate the need matrix
    if(getNeedMatrix(max, allocation) == 1) {
      // Need matrix calculated successfully

      if (isSafe(available, allocation, need, finish, available, path, 0) == 0) {
        
        // Unsafe schedule
        printf("UNSAFE: ");
        for (int i=0; i<num_threads; i++) {
          printf("T%d ", i);
        }
        printf(" can't finish\n");
      
      } 
      
      // Integrity fail in the need matrix
      else if (isSafe(available, allocation, need, finish, available, path, 0) == 2) {
        printf("Integrity test failed: allocated resources exceed total resources\n");
      } 

      // Success, print the matrices
      else {
        printPath(path, num_threads);
      }
    }

    // Free everything
    freeup();

    // Close the file
    fclose(file);
  } 
  
  // Not enough parameters
  else if (argc == 1) {
    printf("Not enough arguments. Please try\n./bankers <file to test>\n");
  } 

  // Too many parameters
  else if (argc > 2) {
    printf("Too many arguments. Please try\n./bankers <file to test>\n");
  }
  
  // Can't find file
  else {
    printf("Can't find file %s\n", argv[1]);
  }

  return 0;
}

