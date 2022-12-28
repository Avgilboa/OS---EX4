#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>

int main()
{
    time_t start = time(NULL);
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
    }
    printf("wake a task using signal packet: ");
    printf("%.4f second \n", (double)(time(NULL) - start));
}