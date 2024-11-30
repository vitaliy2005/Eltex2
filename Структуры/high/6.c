#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Определение структуры узла списка
typedef struct Node
{
    int32_t taskId;
    int32_t priority;
    char taskName[30];
    struct Node* next;
} Node;

// Функция для создания нового узла
Node* create_node(char* taskName, int32_t priority, int32_t taskId)
{
    Node* new_node = malloc(sizeof(Node));
    if (!new_node)
    {
        perror("Не удалось выделить память");
        return NULL;
    }
    strcpy(new_node->taskName, taskName);
    new_node->priority = priority;
    new_node->taskId = taskId;
    new_node->next = NULL;

    return new_node;
}

void add_by_priority(Node** head, char* taskName, int32_t priority, int32_t taskId)
{
    Node* new_node = create_node(taskName, priority, taskId);
    if (!new_node)
    {
        perror("Не удалось выделить память");
        return;
    }

    if (*head == NULL || (*head)->priority < priority)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL && current->next->priority >= priority)
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

// Функция для удаления задачи по ID
void delete_at(Node** head, int32_t taskId)
{
    if (!*head)
    {
        printf("Элементов в списке нет\n");
        return;
    }

    Node* current = *head;
    Node* prev = NULL;

    // Если удаляемый элемент — голова списка
    if (current->taskId == taskId)
    {
        *head = current->next;
        free(current);
        printf("Задача с ID %d удалена.\n", taskId);
        return;
    }

    // Поиск узла с указанным ID
    while (current != NULL && current->taskId != taskId)
    {
        prev = current;
        current = current->next;
    }

    // Если узел не найден
    if (!current)
    {
        printf("Задача с ID %d не найдена.\n", taskId);
        return;
    }

    // Удаление найденного узла
    prev->next = current->next;
    free(current);
    printf("Задача с ID %d удалена.\n", taskId);
}

// Функция для печати списка задач
void print_list_task(Node* head)
{
    if (!head)
    {
        printf("Элементы отсутствуют\n");
        return;
    }

    Node* current = head;
    printf("Элементы списка:\n");
    while (current)
    {
        printf("ID: %d, Имя: %s, Приоритет: %d\n", current->taskId, current->taskName, current->priority);
        current = current->next;
    }
}

// Функция для освобождения памяти списка
void free_tasks(Node* head)
{
    Node* current = head;
    Node* next = NULL;

    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int32_t main()
{
    // Создаем первый узел списка
    Node* head = create_node("Task 1", 2, 112);

    // Добавляем задачи в список
    add_by_priority(&head, "Задача A", 2, 111);
    add_by_priority(&head, "Задача B", 5, 41);
    add_by_priority(&head, "Задача C", 3, 52);
    add_by_priority(&head, "Задача D", 1, 145);

    // Печатаем список
    print_list_task(head);

    // Удаляем задачу с ID 52
    delete_at(&head, 52);

    // Печатаем список после удаления
    print_list_task(head);

    // Освобождаем память
    free_tasks(head);

    return 0;
}
