#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int count = 0;


void* fuel_filling(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutexFuel);
        count++;
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
    }
}

void* car(void* arg) {
    printf("start");
    pthread_mutex_lock(&mutexFuel);
    while (count < 1000000) {
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }

    pthread_mutex_unlock(&mutexFuel);
}

int main(int argc, char* argv[]) {
    time_t start = time(NULL);
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    printf("wake a task using signal cond: ");
    printf("%.4f second \n", (double)(time(NULL) - start));
    return 0;
}