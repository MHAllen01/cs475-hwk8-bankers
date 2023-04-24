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
    fscanf(file, "%d", &num_resources);
    fscanf(file, "%d", &num_threads);

    int available[num_resources];
    int temp, counter = 0;
    
    while(fscanf(file, "%d", &temp) == 1) {
      available[counter++] = temp;
    }

    int max[num_resources][num_threads];

    for (int i=0; i<num_resources; i++) {
      for (int j=0; j<num_threads; j++) {
        fscanf(file, "%d", &max[i][j]);
      }
    }



    for (int j = 0; j < counter; j++) {
        printf("%d ", available[j]);
    }

    for (int i = 0; i < num_resources; i++) {
        for (int j = 0; j < num_threads; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
    printf("\n");



    // Close the file
    fclose(file);
  } else {
    printf("whoops\n");
  }
  return 0;
}