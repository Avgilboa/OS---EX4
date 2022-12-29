#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

// Number of lock/unlock operations to perform
#define NUM_ITERATIONS 1000000

int main(void)
{
    // Open a file for reading and writing
    int fd = open("file.txt", O_RDWR);

    // Get the current time
    clock_t start = clock();

    // Perform the lock/unlock operations
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        // Lock the file
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        fcntl(fd, F_SETLKW, &lock);

        // Unlock the file
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
    }

    // Get the elapsed time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the elapsed time
    printf("wake a task using lock fctl - %f seconds\n", elapsed_time);

    // Close the file
    close(fd);
    return 0;
}
