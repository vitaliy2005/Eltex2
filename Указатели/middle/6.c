#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 2
#define BUFFER_SIZE 100


typedef struct
{
    char **data;
    int32_t count;
    int32_t capacity;
} StringArray;


void init_string_array(StringArray *arr)
{
    arr->data = malloc(INITIAL_CAPACITY * sizeof(char *));
    arr->count = 0;
    arr->capacity = INITIAL_CAPACITY;
}


void add_string(StringArray *arr, const char *str)
{
    if (arr->count >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(char *));
    }

    arr->data[arr->count] = malloc(strlen(str) + 1);
    strcpy(arr->data[arr->count], str);
    arr->count++;
}


bool delete_string(StringArray *arr, int32_t index)
{
    if (index < 0 || index >= arr->count)
    {
        printf("Неверный индекс.\n");
        return 0;
    }

    free(arr->data[index]);

    for (int32_t i = index; i < arr->count - 1; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }
    arr->count--;

    return 1;
}


bool display_strings(const StringArray *arr)
{
    if (arr->count == 0)
    {
        printf("Массив строк пуст.\n");
        return 0;
    }

    for (int32_t i = 0; i < arr->count; i++)
    {
        printf("%d: %s\n", i, arr->data[i]);
    }

    return 1;
}


void free_string_array(StringArray *arr)
{
    for (int32_t i = 0; i < arr->count; i++)
    {
        free(arr->data[i]);
    }
    free(arr->data);
}


void disable_buffered_input()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}


void enable_buffered_input()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}


void clear_screen()
{
    printf("\033[2J");
    printf("\033[H");
}


void display_menu(int32_t selected)
{
    const char *options[] =
    {
        "Добавить строку",
        "Удалить строку по индексу",
        "Вывести все строки",
        "Выйти"
    };
    int32_t num_options = sizeof(options) / sizeof(options[0]);

    clear_screen();
    printf("\033[1;34mМеню:\033[0m\n");

    for (int32_t i = 0; i < num_options; i++)
    {
        if (i == selected)
        {
            printf("\033[1;32m> %s\033[0m\n", options[i]);
        }
        else
        {
            printf("  %s\n", options[i]);
        }
    }
}

int32_t main()
{
    StringArray arr;
    init_string_array(&arr);
    disable_buffered_input();

    char choice;
    char buffer[BUFFER_SIZE];
    int32_t selected = 0;
    int32_t exit_program = 0;

    while (!exit_program)
    {
        display_menu(selected);
        choice = getchar();

        switch (choice)
        {
            case 'w':
                if (selected > 0) selected--;
                break;
            case 's':
                if (selected < 3) selected++;
                break;
            case '\n':
                switch (selected)
                {
                    case 0:
                        printf("Введите строку: ");
                        fflush(stdout);
                        fgets(buffer, sizeof(buffer), stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        add_string(&arr, buffer);
                        printf("Строка добавлена.\nНажмите любую кнопку чтобы прододжить.\n");
                        getchar();
                        break;

                    case 1:
                        clear_screen();
                        printf("Текущие строки:\n");
                        if (display_strings(&arr))
                        {
                            printf("Введите индекс для удаления: ");
                            fflush(stdout);
                            int32_t index;
                            if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &index) == 1)
                            {
                                    if (delete_string(&arr, index))
                                        printf("Строка удалена. Нажмите любую кнопку чтобы прододжить.\n");
                                    else
                                        printf("Не удалось удалить строку. Нажмите любую кнопку чтобы прододжить.\n");
                            }
                            else
                            {
                                printf("Введено некорректное значение. Нажмите любую кнопку чтобы прододжить.\n");
                            }
                            getchar();
                            break;
                        }
                        else
                        {
                            printf("Нажмите любую кнопку чтобы прододжить.\n");
                        }
                        getchar();
                        break;
                    case 2:
                        printf("Текущие строки:\n");
                        display_strings(&arr);
                        printf("Нажмите любую кнопку чтобы прододжить.\n");
                        getchar();
                        break;

                    case 3:
                        exit_program = 1;
                        break;
                }
                break;

            default:
                printf("Неверный ввод. Используйте 'w', 's' и Enter.\n");
                getchar();
                break;
        }
    }

    free_string_array(&arr);
    enable_buffered_input();
    clear_screen();
    printf("Программа завершена.\n");
}
