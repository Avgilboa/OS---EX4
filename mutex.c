#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);

        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    time_t start = time(NULL);

    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_join(p1, NULL) != 0) {
        return 5;
    }

    pthread_mutex_destroy(&mutex);
    printf("wake a task using lock mutex: ");
    printf("%.4f second \n", (double)(time(NULL) - start));

    return 0;
}