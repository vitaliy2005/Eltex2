#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define QUEUE_KEY 1234
#define MAX_MESSAGES 10

struct message
{
    long mtype;
    int32_t data;
};

int main()
{
    int msgid;
    pid_t pid;
    struct timespec start, end;

    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1)
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

    if (pid == 0)
    {
        struct message msg;
        for (int i = 0; i < 1000000; i++)
        {
            if (msgrcv(msgid, &msg, sizeof(int32_t), 1, 0) == -1)
            {
                perror("Error receiving message");
            }
        }
        exit(0);
    }
    else
    {
        struct message msg;
        msg.mtype = 1;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < 1000000; i++)
        {
            msg.data = i;
            if (msgsnd(msgid, &msg, sizeof(int32_t), 0) == -1)
            {
                perror("Error sending message");
                return -1;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("FIFO Receiver: Time taken: %f seconds\n", time_taken);
        wait(NULL);
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
