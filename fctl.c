#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
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

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error locking file");
        return 1;
    }

    getchar();

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error unlocking file");
        return 1;
    }

    close(fd);

    return 0;
}