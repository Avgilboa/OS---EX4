#include <stdio.h>
#include <time.h>
#include <pthread.h>

// Number of lock/unlock operations to perform
#define NUM_ITERATIONS 1000000

pthread_cond_t cond;
pthread_mutex_t mutex;

// Thread function
void* thread_func(void* arg) {
    // Perform the lock/unlock operations
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void) {

    // Get the current time
    clock_t start = clock();


    // Get the elapsed time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the elapsed time
    printf("Elapsed time: %f seconds\n", elapsed_time);

    // Clean up the mutex and condition variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
