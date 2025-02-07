#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define QUEUE_NAME "/mq_my"
#define MAX_MESSAGES 10
#define MSG_SIZE sizeof(int32_t)


int32_t main()
{
    int32_t pid;
    mqd_t mq, fd_mq;
    struct timespec start, end;
    struct mq_attr attr =
    {
        .mq_flags = 0,
        .mq_curmsgs = 0,
        .mq_maxmsg = MAX_MESSAGES,
        .mq_msgsize = MSG_SIZE
    };

    mq_unlink(QUEUE_NAME);
    if((mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr)) == (mqd_t)-1)
    {
        perror("Error creating message queue");
        return -1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error fork");
        return -1;
    }
    if(pid == 0)
    {
        if((fd_mq = mq_open(QUEUE_NAME, O_RDONLY)) == -1)
        {
            perror("Error open queue for read");
            exit(-1);
        }

        int32_t num;
        for (int32_t i = 0; i < 1000000; i++)
        {
            if(mq_receive(fd_mq, (char*)&num, sizeof(int32_t), 0) == -1)
            {
                perror("Error read queue");
                exit(-1);
            }
        }

        if(mq_close(fd_mq) == -1)
        {
            perror("Error close in child");
            exit(-1);
        }
        exit(0);
    }
    else
    {
        if((fd_mq = mq_open(QUEUE_NAME, O_WRONLY)) == -1)
        {
            perror("Error open queue for write");
            return -1;
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int32_t i = 0; i < 1000000; i++)
        {
            if(mq_send(fd_mq, (const char*)&i, sizeof(int32_t), 0) == -1)
            {
                perror("Error write");
                return -1;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("FIFO Receiver: Time taken: %f seconds\n", time_taken);
        if(mq_close(fd_mq) == -1)
        {
            perror("Error close in parent");
            return -1;
        }
        wait(NULL);
    }

    unlink(QUEUE_NAME);
}
