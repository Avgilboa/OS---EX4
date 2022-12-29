#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<time.h>

int main()
{
    clock_t start = clock();
    int sv[2];
    char buf;
    if (socketpair(AF_UNIX,SOCK_STREAM,0,sv) == -1)
    {
        perror("socketpair");
        exit(1);
    }
    if (!fork()) //child
    {
        for (int i = 0; i < 1000000; i++)
        {
            read(sv[1],&buf,1);
            write(sv[1],&buf,1);
        }
        exit(0);
    }
    else //parent
    {
        for (size_t i = 0; i < 1000000; i++)
        {        
            write(sv[0],"1",1);
            read(sv[0],&buf,1);
        }
        wait(NULL);
        clock_t end = clock();
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("wake a task using signal packet - ");
        printf("%f seconds\n", elapsed_time);
        return 0;
    }

}