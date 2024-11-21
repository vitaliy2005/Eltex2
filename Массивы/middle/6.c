#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>


typedef struct
{
    int32_t* data;
    int32_t current_size;
    int32_t size;
}Queue_t;

Queue_t* init_queue(int32_t size)
{
    Queue_t* queue = malloc(sizeof(Queue_t));
    if (queue == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    queue->size = size;
    queue->data = malloc(sizeof(int32_t) * size);
    queue->current_size = 0;

    return queue;
}

void enqueue(Queue_t* queue, int32_t item)
{
    if(queue->current_size < queue->size)
    {
        queue->data[queue->current_size++] = item;
    }
    else
    {
        printf("Очередь переполнена\n");
    }
}

void dequeue(Queue_t* queue)
{
    if(queue->current_size == 0)
    {
        printf("Очередь пуста\n");

        return;
    }

    queue->current_size--;
}

bool is_empty(Queue_t* queue)
{
    return queue->current_size == 0;
}

void free_queue(Queue_t* queue)
{
    free(queue->data);
    free(queue);
}




int32_t main()
{
    Queue_t* queue = init_queue(3);

    for(int32_t i = 0; i < queue->size; i++)
    {
        printf("%b\n", is_empty(queue));
        enqueue(queue, i);
    }

    for (int32_t i = 0; i < queue->size; i++)
    {
        dequeue(queue);
    }
    printf("%b\n", is_empty(queue));

    free_queue(queue);
}
