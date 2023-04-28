#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here

/**
 * @param   available       - The available amount of resources
 * @param   allocation      - The number of allocated resources
 * @param   need            - The number of needed resources
 * 
 * @return  1 if is safe path, 0 otherwise
*/
// int isSafee(int* available, int** allocation, int** need, int* path) {
//     // Keeps track of the order threads finished
//     int schedule[num_threads];

//     // "CLONE" the available resources -- leave available untouched
//     // (Copy the array into another array)
//     int work[num_resources];
//     for (int i=0; i<num_resources; i++) {
//         work[i] = available[i];
//     }

//     // Create an array of threads that have finished their job
//     // 0 is job not finished -- Initalize to 0
//     // 1 is job finished
//     int finish[num_threads];
//     for (int i=0; i<num_threads; i++) {
//         finish[i] = 0;
//     }

//     // While there is an unfinished thread
//     // and the row of need is <= work (work is a row too)
//     // (row of need == thread section)
//     int counter = 0; // Incremental counter for while loop
//     while(finish[counter] == 0 && compareRow(need[counter], work) == 1) {
//         // Thread i can finish execution
//         // Reclaim its allocated resources to check for another thread
//         for (int i=0; i<num_threads; i++) {
//             for (int j=0; j<num_resources; j++) {
//                 work[j] += allocation[i][j];
//             }
            
//             // Record the schedule
//             schedule[counter] = i;
//         }

//         // Set the thread to being complete
//         finish[counter] = 1;

//         // Increment the counter
//         counter++;
//     }

//     /*  
//         Check the finish array
//         If any thread is at 0, then the schedule is unsafe => return 0
//         Otherwise, return 1
//     */

//     // Boolean check to see if the current schedule is safe
//     int unsafe = 0;

//     // Find any unsafe threads
//     for (int i=0; i<num_threads; i++) {
//         if (finish[i] == 0) {
//             unsafe = 1;
//         }
//     }

//     if (unsafe == 1) {
//         // If unsafe == 1, there is an unsafe schedule
//         printf("UNSAFE:  ");
//         for (int i=0; i<num_threads; i++) {
//             if (finish[i] == 0) {
//                 printf("T%d ", i);
//             }
//         }
//         printf(" can't finish\n");
//         return 0;
//     } else {
//         // Schedule is safe, print it

//         printf("SAFE:  ");
//         for (int i=0; i<num_resources; i++) {
//             printf("T%d ", schedule[i]);
//         }
//     }

//     return 1;
// }



int isSafe(int* available, int** allocated, int** need, int* finish, int* work, int* path, int thread_num) {
    // "CLONE" the available resources -- leave available untouched
    // (Copy the array into another array)
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    // Boolean-like integer to keep track of the safety of a thread
    int safe = 0;

    // Find out if a schedule is safe
    // Loop through the threads by grabbing the ith row of the need matrix
    for (int i = 0; i < num_threads; i++) {

        // If there is an unfinished thread
        // and the row of need is <= work (work is a row too)
        // (row of need == thread section)
        if (finish[i] == 0 && compareRow(need[i], work) == 1) {

            // Set the thread to finished
            finish[i] = 1;

            // Reclaim the allocated resources to the work vector
            for (int j=0; j<num_resources; j++) {
                work[j] += allocated[i][j];
            }

            // Record the thread as a successful thread
            path[thread_num] = i;

            // Check if this state is safe using recursion
            if (isSafe(available, allocated, need, finish, work, path, thread_num+1)) {
                // Thread is safe
                safe = 1;

                // If the thread number that is safe == the thread number that is safe (from total threads - 1)...
                if (thread_num == num_threads - 1) {
                    // Print the safe schedule
                    printPath(path, thread_num+1);
                }
            }

            // Set the thread back to unfinished for recursion
            finish[i] = 0;

            // Allocate the resources again for recursion
            for (int j=0; j<num_resources; j++) {
                work[j] -= allocated[i][j];
            }

        } else if (compareRow(need[i], work) != 1) {
            // There is an integrity error, return out of the function
            // Error
            return 2;
        }
    }

    // If the safe boolean isn't 1
    if (safe != 1) {

        for (int i = 0; i < num_threads; i++) {
            if (finish[i] == 0) {
                // Return out since there is an unsafe thread
                // Used for unsafe schedule reporting
                // Error
                return 0;
            }
        }
    }

    // Successful
    return 1;
}


/**
 * Prints the safe schedule of threads
 * 
 * @param   path        - The path of threads to print
 * @param   thread_num  - The current thread number to print
*/
void printPath(int* path, int thread_num) {
    printf("SAFE:  ");
    for (int i = 0; i < thread_num; i++) {
        printf("T%d ", path[i]);
    }
    printf("\n");
}



