/* declarations related to banker's algorithm */

// Globals in main.c
extern int num_resources;
extern int num_threads;

extern int *available;
extern int **max;
extern int **allocation;
extern int **need;
extern int *path;

int isSafe(int* available, int** allocated, int** need, int* finish, int* work, int* path, int thread_num);
void printPath(int* path, int length);