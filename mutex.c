#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);

        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    clock_t start = clock();

    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_join(p1, NULL) != 0) {
        return 5;
    }

    pthread_mutex_destroy(&mutex);
    // Get the elapsed time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the elapsed time
    printf("wake a task using lock mutex - %f seconds\n", elapsed_time);

    return 0;
}