#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#include <wait.h>


#define SIZE_BUFFER_I 2
#define SIZE_BUFFER_J 100
#define SHM_SIZE sizeof(ring_buffer)
#define SHM_NAME "/my_shm"


typedef struct ring_buffer
{
    sem_t mutex;
    sem_t full;
    char buffer[SIZE_BUFFER_I][SIZE_BUFFER_J];
    int32_t read;
    int32_t write;
}ring_buffer;

bool is_empty(ring_buffer* ring_buf)
{
    int32_t value;
    sem_getvalue(&ring_buf->full, &value);

    return (value == SIZE_BUFFER_I);
}

void reader(ring_buffer* ring_buf)
{
    for (;;)
    {
        sem_wait(&ring_buf->mutex);

        if(is_empty(ring_buf))
        {
            sem_post(&ring_buf->mutex);
            sleep(1);
            continue;
        }

        printf("прочитано %s\n", ring_buf->buffer[ring_buf->read]);
        ring_buf->read = (ring_buf->read + 1) % SIZE_BUFFER_I;
        if (strcmp(ring_buf->buffer[ring_buf->read], "END") == 0)
        {
            sem_post(&ring_buf->mutex);
            break;
        }

        sem_post(&ring_buf->full);
        sem_post(&ring_buf->mutex);
        sleep(2);
    }
}

void writer(ring_buffer* ring_buf)
{
    int32_t value;
    for (int32_t i = 0; i < 10; i++)
    {
        sem_wait(&ring_buf->full);

        snprintf(ring_buf->buffer[ring_buf->write], SIZE_BUFFER_J, "Message %d", i);
        ring_buf->write = (ring_buf->write + 1) % SIZE_BUFFER_I;

        sleep(1);
    }

    sem_wait(&ring_buf->full);
    snprintf(ring_buf->buffer[ring_buf->write], SIZE_BUFFER_J, "END");
    ring_buf->write = (ring_buf->write + 1) % SIZE_BUFFER_I;
    sem_wait(&ring_buf->full);
    snprintf(ring_buf->buffer[ring_buf->write], SIZE_BUFFER_J, "END");
    ring_buf->write = (ring_buf->write + 1) % SIZE_BUFFER_I;
}

ring_buffer* init_ring_buffer(ring_buffer* ring_buf)
{
    int32_t shm_fd;

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("Error shm_open");
        return NULL;
    }

    ftruncate(shm_fd, SHM_SIZE);

    ring_buf = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ring_buf == MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }
    if (sem_init(&ring_buf->full, 1, SIZE_BUFFER_I) == -1)
    {
        perror("sem_init");
        return NULL;
    }
    if (sem_init(&ring_buf->mutex, 1, 1) == -1)
    {
        perror("sem_init");
        return NULL;
    }
    ring_buf->read = 0;
    ring_buf->write = 0;

    return ring_buf;
}

int32_t main()
{
    pid_t pid;
    ring_buffer* ring_buf = init_ring_buffer(ring_buf);

    if(ring_buf == NULL)
    {
        return -1;
    }

    pid = fork();
    if(pid == 0)
    {
        writer(ring_buf);
        exit(0);
    }
    else if (pid == -1)
    {
        perror("Error fork");
        return -1;
    }

    pid = fork();
    if(pid == 0)
    {
        reader(ring_buf);
        exit(0);
    }
    else if (pid == -1)
    {
        perror("Error fork");
        return -1;
    }

    pid = fork();
    if(pid == 0)
    {
        reader(ring_buf);
        exit(0);
    }
    else if (pid == -1)
    {
        perror("Error fork");
        return -1;
    }

    while (wait(NULL) > 0);

    munmap(ring_buf, SHM_SIZE);
    shm_unlink(SHM_NAME);
    sem_destroy(&ring_buf->mutex);
    sem_destroy(&ring_buf->full);
}
