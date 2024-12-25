#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int32_t num;
    char str[40];
} TASK2;

void task1()
{
    const int32_t SIZE = 10;
    int32_t* nums = malloc(sizeof(int32_t) * SIZE);
    if(!nums)
    {
        perror("Ошибка выделения памяти");
        return;
    }

    for (int32_t i = 0; i < SIZE; i++)
    {
        *(nums+i) = i*i;
        printf("%d ", *(nums+i));
    }
    printf("\n");

    free(nums);
}

void task2()
{
    const int32_t SIZE = 10;
    TASK2* st = calloc(SIZE, sizeof(int32_t));
    if(!st)
    {
        perror("Ошибка выделения памяти");
        return;
    }

    for (int32_t i = 0; i < SIZE; i++)
    {
        st->num = i*i;
        sprintf(st->str, "'i = %d'", i);
        printf("Поле целочисленное = %d, строковое = %s\n", st->num, st->str);
    }
    printf("\n");

    free(st);
}

void task3()
{
    const int32_t FIRST_LEN = 3;
    const int32_t SECOND_LEN = 9;
    const int32_t BUFFER_SIZE = 128;

    char **array = (char**)malloc(FIRST_LEN * sizeof(char *));
    if (!array)
    {
        perror("Ошибка выделения памяти:");
        return;
    }

    printf("Введите %d строк:\n", FIRST_LEN);
    for (int32_t i = 0; i < FIRST_LEN; i++)
    {
        array[i] = (char*)malloc(BUFFER_SIZE * sizeof(char));
        if (!array[i])
        {
            perror("Ошибка выделения памяти для строки:");
            return;
        }
        printf("Строка %d: ", i + 1);
        fgets(array[i], BUFFER_SIZE, stdin);
        array[i][strcspn(array[i], "\n")] = '\0';
    }

    array = (char **)realloc(array, SECOND_LEN * sizeof(char *));
    if (!array)
    {
        perror("Ошибка перераспределения памяти:");
        for (int32_t i = 0; i < FIRST_LEN; i++)
        {
            free(array[i]);
        }
        free(array);
        return;
    }

    printf("\nВведите %d дополнительных строк:\n", SECOND_LEN - FIRST_LEN);
    for (int32_t i = FIRST_LEN; i < SECOND_LEN; i++)
    {
        array[i] = (char*)malloc(BUFFER_SIZE * sizeof(char));
        if (!array[i])
        {
            perror("Ошибка выделения памяти для новой строки:");
            for (int32_t j = 0; j < i; j++)
            {
                free(array[j]);
            }
            free(array);
            return;
        }
        printf("Строка %d: ", i + 1);
        fgets(array[i], BUFFER_SIZE, stdin);
        array[i][strcspn(array[i], "\n")] = '\0';
    }

    printf("\nВсе строки:\n");
    for (int32_t i = 0; i < SECOND_LEN; i++)
    {
        printf("Строка %d: %s\n", i + 1, array[i]);
    }

    for (int32_t i = 0; i < SECOND_LEN; i++)
    {
        free(array[i]);
    }
    free(array);
}

void task4()
{
    const int32_t SIZE_STR = 50;
    char *leaked_memory = (char*)malloc(SIZE_STR * sizeof(char));
    if (!leaked_memory)
    {
        perror("Ошибка выделения памяти:");
        return;
    }

    printf("Сообщение: Эта память будет освобождена.\n");

    // free(leaked_memory); //нужно убрать комментарий, чтобы исправить утечку памяти
}

 long long task5(int n, int depth)
 {
    printf("Глубина рекурсии: %d, адрес переменной n: %p, значение n: %d\n", depth, (void*)&n, n);
    if (n <= 1)
    {
        return 1;
    }

    return n * task5(n - 1, depth + 1);
 }

 void task6()
 {
    const int32_t ARRAY_SIZE = 5;
    const int32_t STRING_SIZE = 64;
    char* static_array[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        static_array[i] = (char*)malloc(STRING_SIZE * sizeof(char));
        if (!static_array[i])
        {
            perror("Ошибка выделения памяти:");
            for (int32_t j = 0; j < i; i++)
            {
                free(static_array[j]);
            }
            return;
        }

        printf("Введите строку %d: ", i + 1);
        fgets(static_array[i], STRING_SIZE, stdin);

        static_array[i][strcspn(static_array[i], "\n")] = '\0';
    }

    printf("\nВы ввели следующие строки:\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("Строка %d: %s\n", i + 1, static_array[i]);
    }

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        free(static_array[i]);
    }

 }

int32_t main(int32_t argc, char** argv)
{
    int32_t choice;
    do
    {
        printf("\n");
        printf("1.Динамическое выделение массива:\n");
        printf("  Напишите программу, которая выделяет память для массива целых чисел,\n"
            "используя malloc. Заполните массив значениями и выведите их. Освободите выделенную память с помощью free.\n\n");

        printf("2: Инициализация памяти с помощью calloc\n");
        printf("  Создайте программу, которая выделяет память для массива структур, каждая из которых содержит два поля: целочисленное и строковое."
            "\nИспользуйте calloc для инициализации памяти. Заполните структуры данными и выведите их содержимое.\n\n");

        printf("3: Реализация функции увеличения массива\n");
        printf("  СРеализуйте программу, которая динамически увеличивает размер массива строк с использованием realloc."
            "  Изначально выделите память для нескольких строк, затем увеличьте размер массива и добавьте новые строки. Выведите все строки и освободите память.\n\n");

        printf("4: Работа с указателями и утечками памяти\n");
        printf("  Напишите программу с примером утечки памяти, где выделенная память не освобождается."
           "Используйте valgrind или другой инструмент для анализа и устранения утечки.\n\n");

        printf("5: Изучение стека и локальной памяти\n"
        "  Создайте рекурсивную функцию, которая вычисляет факториал числа.\n"
        "Изучите, как стек используется для хранения локальных переменных и как изменяется его размер при увеличении глубины рекурсии.\n\n");

        printf("6: Смешанное использование статической и динамической памяти\n"
        "  Реализуйте программу, которая использует как статическую, так и динамическую память. Создайте статический массив для хранения указателей на динамически выделенные строки.\n"
        "Заполните массив строками, выведите их и освободите динамическую память.\n\n");

        printf("Выбирите задачу: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            {
                system("clear");
                task1();
                break;
            }

            case 2:
            {
                system("clear");
                task2();
                break;
            }
            case 3:
            {
                system("clear");
                task3();
                break;
            }
            case 4:
            {
                system("clear");
                task4();
                break;
            }
            case 5:
            {
                system("clear");
                task5(5, 5);
                break;
            }
            case 6:
            {
                system("clear");
                task6();
            }
        }
    } while(choice);

    return 0;
}
