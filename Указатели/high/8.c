#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <threads.h>


typedef enum
{
    INT,
    FLOAT,
    STRING
} type_item;

typedef struct Node
{
    type_item type;
    void* item;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct Dbl_linked_list
{
    size_t size;
    Node* head;
    Node* tail;
} Dbl_linked_list;

Node* create_node(type_item type, void* item);
Dbl_linked_list* create_dbl_linked_list();
void delete_dbl_linked_list(Dbl_linked_list* list);
void insert_at(Dbl_linked_list* list, size_t index, type_item type, void* item);
void delete_at(Dbl_linked_list* list, size_t index);
void append(Dbl_linked_list* list, type_item type, void* item);
void print_dbl_linked_list(Dbl_linked_list* list);


Node* create_node(type_item type, void* item)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node)
    {
        new_node->type = type;
    }
    else
    {
        perror("Не удалось выделить память");
        return NULL;
    }

    switch (type)
    {
        case INT:
        {
            new_node->item = malloc(sizeof(int64_t));
            memcpy(new_node->item, item, sizeof(int64_t));
            break;
        }
        case FLOAT:
        {
            new_node->item = malloc(sizeof(FLOAT));
            memcpy(new_node->item, item, sizeof(float));
            break;
        }
        case STRING:
        {
            new_node->item = malloc(sizeof(strlen((char*)item)+1));
            strcpy(new_node->item, (char*)item);
            break;
        }
    }

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

Dbl_linked_list* create_dbl_linked_list()
{
    Dbl_linked_list* dbl_linked_list = (Dbl_linked_list*)malloc(sizeof(Dbl_linked_list));
    if (!dbl_linked_list)
    {
        perror("Не удалось выделить память");
        return NULL;
    }

    dbl_linked_list->size = 0;
    dbl_linked_list->head = NULL;
    dbl_linked_list->tail = NULL;

    return dbl_linked_list;
}

void delete_dbl_linked_list(Dbl_linked_list* list)
{
    Node* current = list->head;
    Node* next = NULL;

    while (current)
    {
        next = current->next;
        free(current->item);
        free(current);
        current = next;
    }
    free(list);
}

void insert_at(Dbl_linked_list* list, size_t index, type_item type, void* item)
{
    Node* current = list->head;
    Node* new_node = create_node(type, item);
    if (!new_node)
    {
        perror("Не удалось выделить память");
        return;
    }

    size_t current_index = 0;

    if (!index)
    {
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
        return;
    }

    while ( (current_index++ < index - 1) || (current != NULL) )
    {
        current = current->next;
    }

    if (current)
    {
        new_node->next = current->next;
        current->next = new_node;
        new_node->prev = current;
        list->size++;
        return;
    }
    else
    {
        printf("Индекс вне границ\n");
        free(new_node->item);
        free(new_node);
    }
}

void append(Dbl_linked_list* list, type_item type, void* item)
{
    if (!list->size)
    {
        list->head = create_node(type, item);
        if (!list->head)
        {
            perror("Не удалось выделить память");
            return;
        }
        list->tail = list->head;
    }
    else
    {
        Node* tail = list->tail;
        Node* next = create_node(type, item);
        if (!next)
        {
            perror("Не удалось выделить память");
            return;
        }
        tail->next = next;
        next->prev = tail;
        list->tail = next;
    }

    list->size++;
}




void delete_at(Dbl_linked_list* list, size_t index)
{
    if (!list->size)
    {
        printf("Элементов в списке нет\n");
        return;
    }

    if (index >= list->size)
    {
        printf("Выход за границы списка\n");
        return;
    }

    if (!index)
    {
        Node* next = list->head->next;
        free(list->head->item);
        free(list->head);
        list->head = next;
        list->size--;
        return;
    }

    int32_t current_index = 0;
    Node* current_node = list->head;

    while (current_index++ < index)
    {
        current_node = current_node->next;
    }

    Node* temp = current_node->prev;
    temp->next = current_node->next;
    free(current_node->item);
    free(current_node);
    list->size--;
}

void print_dbl_linked_list(Dbl_linked_list* list)
{
    if (!list->size)
    {
        printf("элементы отсутствуют\n");
        return;
    }

    Node* current_node = list->head;
    size_t current_index = 0;

    printf("Элементы списка:\n");
    while (current_index++ < list->size)
    {
        switch (current_node->type)
        {
            case INT:
            {
                printf("%ld\n", *(int64_t*)current_node->item);
                break;
            }
            case FLOAT:
            {
                printf("%f\n", *(float*)current_node->item);
                break;
            }
            case STRING:
            {
                printf("%s\n", (char*)current_node->item);
                break;
            }
        }
        current_node = current_node->next;
    }
}

void search_item(Dbl_linked_list* list, void* item)
{
    if (!list || !list->head)
    {
            printf("Список пуст\n");
            return;
    }

    Node* current_node = list->head;
    while (current_node)
    {
        switch (current_node->type)
        {
            case INT:
            {
                if(*(int64_t*)current_node->item == *(int64_t*)item)
                {
                    printf("элемент %ld есть в списке\n", *(int64_t*)current_node->item);
                    return;
                }
                break;
            }
            case FLOAT:
            {
                if(*(float*)current_node->item == *(float*)item)
                {
                    printf("элемент %f есть в списке\n", *(float*)current_node->item);
                    return;
                }
                break;
            }
            case STRING:
            {
                if(!strcmp((char*)current_node->item, (char*)item))
                {
                    printf("элемент %s есть в списке\n", (char*)current_node->item);
                    return;
                }
                break;
            }
        }
        current_node = current_node->next;
    }

    printf("Элемент не найден\n");
}

int32_t main()
{
    Dbl_linked_list* list = create_dbl_linked_list();

    int64_t a = 2;
    int64_t b = 4;
    int64_t c = 8;

    append(list, INT, &a);
    append(list, INT, &b);
    append(list, STRING, "222");
    search_item(list, &c);
    search_item(list, "222");

    print_dbl_linked_list(list);
    printf("Размер списка: %zu\n", list->size);

    delete_at(list, 3);

    print_dbl_linked_list(list);
    printf("Размер списка: %zu\n", list->size);

    delete_at(list, 0);

    print_dbl_linked_list(list);
    printf("Размер списка: %zu\n", list->size);

    delete_dbl_linked_list(list);
}
