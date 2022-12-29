#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
        // Get the current time
    clock_t start = clock();
    int fd;
    struct flock lock;

    fd = open("file.txt", O_CREAT|O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    lock.l_type = F_LOCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    for(int i=0;i<1000000;i++)
    {
        lock.l_type = F_LOCK;
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("Error locking file");
            return 1;
        }

        lock.l_type = F_UNLCK;

        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("Error unlocking file");
            return 1;
        }
    }
    close(fd);
    remove("file.txt");
    // Get the elapsed time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("wake a task using signal fctl - ");
    // Print the elapsed time
    printf("%f seconds\n", elapsed_time);
    return 0;
}