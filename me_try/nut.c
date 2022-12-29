#include <stdio.h>
#include <time.h>
#include <pthread.h>

// Number of lock/unlock operations to perform
#define NUM_ITERATIONS 10000000

pthread_mutex_t mutex;

int main(void) {
    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Get the current time
    clock_t start = clock();

    // Perform the lock/unlock operations
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
    }

    // Get the elapsed time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the elapsed time
     printf("wake a task using lock mutex: ");
    printf("%f seconds\n", elapsed_time);

    // Clean up the mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}