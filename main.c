#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// Globals
//int num_resources;
//int num_threads;
//int *available;
//int **max;
int **demand;

/**
 * Check:
 * 1. Currently allocated resources don't exceed total number of resources
 * 2. Thread's don't exceed max demands for each resource type
*/



int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures

  // TODO: Run banker's safety algorithm

  // File to open
  FILE *file;
  file = fopen(argv[1], "r");
  
  int num_resources;
  int num_threads;


  if (file != NULL) {
    // File was opened successfully

    // Scan first two lines
    fscanf(file, "%d %d", &num_resources, &num_threads);
    
    // Allocate space for the available resources
    int available[num_resources];
  
    // Scan the available resources
    for (int i=0; i<num_resources; i++) {
      fscanf(file, "%d", &available[i]);
    }

    // Allocate space for the max resources
    int max[num_threads][num_resources];

    // Scan the max resources
    for (int i=0; i<num_threads; i++) {
      for (int j=0; j<num_resources; j++) {
        fscanf(file, "%d", &max[i][j]);
      }
    }

    // Allocate space for the allocated resources
    int allocation[num_threads][num_resources];

    // Scan the allocated resources
    for (int i=0; i<num_threads; i++) {
      for (int j=0; j<num_resources; j++) {
        fscanf(file, "%d", &allocation[i][j]);
      }
    }

  

    // Close the file
    fclose(file);
  } else {
    printf("whoops\n");
  }
  return 0;
}