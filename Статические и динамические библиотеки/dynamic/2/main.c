#include "io.h"
#include "helper.h"
#include "calc.h"
#include <stdio.h>

int32_t main()
{
    disable_buffered_input();
    printf("\033[?25l");

    int32_t selected = 0;
    int32_t choice;
    int32_t exit_program = 0;
    int32_t num_options = sizeof(options) / sizeof(options[0]);
    int32_t a,b;

    while (!exit_program)
    {
        menu(selected);
        print_help_item_selection();
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
                        printf("\033[?25h");

                        printf("Введите число А:");
                        fflush(stdout);
                        if(scanf("%d", &a) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }

                        printf("Введите число В:");
                        fflush(stdout);
                        if(scanf("%d", &b) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }

                        printf("Результат = %d\n", add(a, b));
                        printf("\033[?25l");
                        disable_buffered_input();
                        printf("Нажмите любую кнопку...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 1:
                    {
                        enable_buffered_input();
                        printf("\033[?25h");
                        printf("Введите число А:");
                        fflush(stdout);
                        if(scanf("%d", &a) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }

                        printf("Введите число В:");
                        fflush(stdout);
                        if(scanf("%d", &b) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }
                        printf("Результат = %d\n", subtract(a, b));
                        printf("\033[?25l");
                        disable_buffered_input();
                        printf("Нажмите любую кнопку...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 2:
                    {
                        enable_buffered_input();
                        printf("\033[?25h");
                        printf("Введите число А и число В для умножения\n");
                        printf("Введите число А:");
                        fflush(stdout);
                        if(scanf("%d", &a) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }

                        printf("Введите число В:");
                        fflush(stdout);
                        if(scanf("%d", &b) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }
                        printf("Результат = %d\n", multiply(a, b));
                        printf("\033[?25l");
                        disable_buffered_input();
                        printf("Нажмите любую кнопку...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 3:
                    {
                        double a_d, b_d;
                        enable_buffered_input();
                        printf("\033[?25h");
                        printf("Введите число А и число В для деления A на B\n");
                        printf("Введите число А:");
                        fflush(stdout);
                        if(scanf("%lf", &a_d) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }

                        printf("Введите число В:");
                        fflush(stdout);
                        if(scanf("%lf", &b_d) != 1)
                        {
                            printf("Ошибка: введено некорректное число.\n");
                            return 1;
                        }
                        if(b_d != 0)
                        {
                            printf("Результат = %lf\n", divide(a_d, b_d));
                        }
                        else
                        {
                            printf("%", divide(a_d, b_d));
                        }
                        printf("\033[?25l");
                        disable_buffered_input();
                        printf("Нажмите любую кнопку...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 4:
                    {
                        exit_program++;
                        break;
                    }
                }
                break;
            }
            default:
            {

                print_help_error_input();
                getchar();
            }
        }
    }

    enable_buffered_input();
    printf("\033[?25h");
}
