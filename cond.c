#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;
pthread_cond_t _cond;
int count = 0;


void* count_filling(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&_cond);
    }
}

void* main_counter(void* arg) {
    pthread_mutex_lock(&mutex);
    while (count < 1000000) {
        pthread_cond_wait(&_cond, &mutex);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }

    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[]) {
    clock_t start = clock();
    pthread_t th[2];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&_cond, NULL);
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            if (pthread_create(&th[i], NULL, &count_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &main_counter, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }    
    // Get the elapsed time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&_cond);
    printf("wake a task using signal cond - ");
    // Print the elapsed time
    printf("%f seconds\n", elapsed_time);
    return 0;
}