/* declarations related to banker's algorithm */

// Globals in main.c
extern int num_resources;
extern int num_threads;

extern int *available;
extern int **max;
extern int **allocation;
extern int **need;
extern int *path;
extern int *finish;

int isSafe(int* available, int** allocation, int** need);
void isSafeSchedule(int* work, int** allocation, int** need, int* finish, int* path);