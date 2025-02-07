#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define NAME_FIFO "fifo_my"


int32_t main()
{
    int32_t fd_fifo, pid;
    struct timespec start, end;

    unlink(NAME_FIFO);
    if((mkfifo(NAME_FIFO, 0666)) == -1)
    {
        perror("Error create fifo");
        return -1;;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error fork");
        return -1;
    }
    if(pid == 0)
    {
        if((fd_fifo = open(NAME_FIFO, O_RDONLY)) == -1)
        {
            perror("Error open fifo for read");
            exit(-1);
        }
        int32_t num;
        for (int32_t i = 0; i < 1000000; i++)
        {
            if(read(fd_fifo, &num, sizeof(int32_t)) == -1)
            {
                perror("Error read fifo");
                exit(-1);
            }
        }

        if(close(fd_fifo) == -1)
        {
            perror("Error close in child");
            exit(-1);
        }
        exit(0);
    }
    else
    {
        if((fd_fifo = open(NAME_FIFO, O_WRONLY)) == -1)
        {
            perror("Error open fifo for write");
            return -1;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int32_t i = 0; i < 1000000; i++)
        {
            if(write(fd_fifo, &i, sizeof(int32_t)) <= 0)
            {
                perror("Error write");
                return -1;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("FIFO Receiver: Time taken: %f seconds\n", time_taken);

        if(close(fd_fifo) == -1)
        {
            perror("Error close in parent");
            return -1;
        }
        wait(NULL);
    }
    unlink(NAME_FIFO);
}
