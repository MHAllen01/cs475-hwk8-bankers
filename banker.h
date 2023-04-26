/* declarations related to banker's algorithm */

// Globals in main.c
extern int num_resources;
extern int num_threads;

extern int *available;
extern int **max;
extern int **allocation;
extern int **need;

int isSafe(int *availableMat, int **allocMat, int **needMat);