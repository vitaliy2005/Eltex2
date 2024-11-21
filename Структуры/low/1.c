#include <curses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define SIZE_STRUCT 100
#define MAX_LEN 10


struct abonent
{
    char name[MAX_LEN];
    char second_name[MAX_LEN];
    char tel[MAX_LEN];
};

const char* options[] =
{
    "Добавить абонента",
    "Удалить абонента",
    "Поиск абонентов по имени",
    "Вывод всех записей",
    "Выход",
};

void clear_screen()
{
    printf("\033[2J");
    printf("\033[H");
}

void disable_buffered_input()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enable_buffered_input()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void menu(int32_t selected)
{
    int32_t num_options = sizeof(options) / sizeof(options[0]);

    clear_screen();
    printf("\033[1;34mМеню:\033[0m\n");

    for (size_t i = 0; i <  num_options; i++)
    {
        if (i == selected)
        {
            printf("\033[1;34m> %s\033[0m\n", options[i]);
        }
        else
        {
            printf("  %s\n", options[i]);
        }
    }
}

void remove_newline(char* str)
{
    str[strcspn(str, "\n")] = '\0';
}

void clear_buffer()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void delete_abonent(struct abonent* list_abonents)
{
    int32_t number;
    printf("Введите порядковый номер абонента для удаления (1 - %d): ", SIZE_STRUCT);
    scanf("%d", &number);
    clear_buffer();

    if (number < 1 || number > SIZE_STRUCT || list_abonents[number - 1].name[0] == '\0')
    {
        printf("Неверный порядковый номер или абонент не существует.\n");
        return;
    }

    for (size_t i = number - 1; i < SIZE_STRUCT - 1; i++)
    {
        list_abonents[i] = list_abonents[i + 1];
    }

    memset(&list_abonents[SIZE_STRUCT - 1], 0, sizeof(struct abonent));
    printf("Абонент с порядковым номером %d удален!\n", number);
    printf("Нажмите любую кнопку...\n");
    getchar();
}

void add_abonent(struct abonent* list_abonents)
{
    for (size_t i = 0; i < SIZE_STRUCT; i++)
    {
        if(list_abonents[SIZE_STRUCT-1].name[0] != '\0')
        {
            clear_screen();
            printf("Список абонентов переполнен\n");
            printf("Нажмите любую кнопку...\n");
            getchar();
            break;
        }

        if (list_abonents[i].name[0] == '\0')
        {
            printf("Введите имя: ");
            fgets(list_abonents[i].name, MAX_LEN, stdin);
            if (list_abonents[i].name[strlen(list_abonents[i].name) - 1] != '\n')
            {
                clear_buffer();
                printf("Переполнение ввода! Строка была обрезана.\n");
            }
            remove_newline(list_abonents[i].name);

            printf("Введите фамилию: ");
            fgets(list_abonents[i].second_name, MAX_LEN, stdin);
            if (list_abonents[i].second_name[strlen(list_abonents[i].second_name) - 1] != '\n')
            {
                clear_buffer();
                printf("Переполнение ввода! Строка была обрезана.\n");
            }
            remove_newline(list_abonents[i].second_name);

            printf("Введите телефон: ");
            fgets(list_abonents[i].tel, MAX_LEN, stdin);
            if (list_abonents[i].tel[strlen(list_abonents[i].tel) - 1] != '\n')
            {
                clear_buffer();
                printf("Переполнение ввода! Строка была обрезана.\n");
            }
            remove_newline(list_abonents[i].tel);

            clear_screen();
            if (list_abonents[i].name[0] == '\0' || list_abonents[i].second_name[0] == '\0' || list_abonents[i].tel[0] == '\0' )
            {
                memset(&list_abonents[i], 0, sizeof(list_abonents[i]));
                printf("Есть пустые поля, абонетн не добавлен!\n");
                printf("Нажмите любую кнопку...\n");
                getchar();
            }
            else
            {
                printf("Абонент добавлен!\n");
                printf("Нажмите любую кнопку...\n");
                getchar();
            }

            break;
        }
    }
}

void print_abonents(struct abonent* list_abonents)
{
    printf("Список абонентов:\n");
    for (size_t i = 0; i < SIZE_STRUCT; i++)
    {
        if (list_abonents[i].name[0] != '\0')
        {
            printf("Абонент %zu:\n", i + 1);
            printf("Имя: %s\n", list_abonents[i].name);
            printf("Фамилия: %s\n", list_abonents[i].second_name);
            printf("Телефон: %s\n", list_abonents[i].tel);
            printf("------------------------\n");
        }
        else break;
    }
}

void search_abonent_by_name(struct abonent* list_abonents)
{
    int32_t found = 0;
    char search_name[MAX_LEN];

    printf("Введите имя абонента для поиска: ");
    fgets(search_name, MAX_LEN, stdin);
    search_name[strcspn(search_name, "\n")] = '\0';

    for (size_t i = 0; list_abonents[i].name[0] != '\0' && i < SIZE_STRUCT; i++)
    {
        if (strcmp(list_abonents[i].name, search_name) == 0)
        {
            printf("Абонент найден!\n");
            printf("Имя: %s\n", list_abonents[i].name);
            printf("Фамилия: %s\n", list_abonents[i].second_name);
            printf("Телефон: %s\n", list_abonents[i].tel);
            found++;
            break;
        }
    }

    if (!found)
    {
        printf("Абонент с именем '%s' не найден.\n", search_name);
    }
}

int32_t main()
{
    disable_buffered_input();
    printf("\033[?25l");

    int32_t selected = 0;
    int32_t choice;
    int32_t exit_program = 0;
    int32_t num_options = sizeof(options) / sizeof(options[0]);
    struct abonent list_abonents[SIZE_STRUCT] = {0};

    while (!exit_program)
    {
        menu(selected);
        choice = getchar();

        switch (choice)
        {
            case 'w':
            case 65:
            {
                if (selected > 0) selected--;
                break;
            }
            case 's':
            case 66:
            {
                if (selected < num_options-1) selected++;
                break;
            }
            case '\n':
            {
                switch (selected)
                {
                    case 0:
                    {
                        enable_buffered_input();
                        clear_screen();
                        printf("\033[?25h");
                        add_abonent(list_abonents);
                        printf("\033[?25l");
                        disable_buffered_input();
                        break;
                    }
                    case 1:
                    {
                        enable_buffered_input();
                        clear_screen();
                        printf("\033[?25h");
                        delete_abonent(list_abonents);
                        printf("\033[?25l");
                        disable_buffered_input();
                        break;
                    }
                    case 2:
                    {
                        enable_buffered_input();
                        clear_screen();
                        printf("\033[?25h");
                        search_abonent_by_name(list_abonents);
                        printf("Нажмите любую кнопку...\n");
                        getchar();
                        disable_buffered_input();
                        printf("\033[?25h");
                        break;
                    }
                    case 3:
                    {
                        clear_screen();
                        print_abonents(list_abonents);
                        printf("Нажмите любую кнопку...\n");
                        getchar();
                        break;
                    }
                    case 4:
                    {
                        clear_screen();
                        exit_program++;
                        break;
                    }
                }
                break;
            }
            default:
            {

                printf("Неверный ввод. Используйте 'w', 's' или стрелки 'вверх' и 'вниз' и Enter.\n");
                getchar();
            }
        }
    }

    enable_buffered_input();
    printf("\033[?25h");
}
