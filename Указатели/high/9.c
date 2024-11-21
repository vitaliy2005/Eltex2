#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

typedef double (*math_function)(double);

double integrate_trapezoidal(math_function func, double a, double b, int32_t n)
{
    double h = (b - a) / n;
    double integral = 0.5 * (func(a) + func(b));

    for (size_t i = 1; i < n; i++)
    {
        double x = a + i * h;
        integral += func(x);
    }

    return integral * h;
}

double integrate_simpson(math_function func, double a, double b, int32_t n)
{
    if (n % 2 != 0)
    {
        printf("Для метода Симпсона требуется четное число интервалов. Увеличиваем n на 1.\n");
        n++;
    }

    double h = (b - a) / n;
    double integral = func(a) + func(b);

    for (size_t i = 1; i < n; i++)
    {
        double x = a + i * h;
        if (i % 2 == 0)
        {
            integral += 2 * func(x);
        }
        else
        {
            integral += 4 * func(x);
        }
    }

    return integral * h / 3.0;
}

double square(double x)
{
    return x * x;
}

double sine(double x)
{
    return sin(x);
}

double exponential(double x)
{
    return exp(x);
}

int32_t main()
{
    double a, b;
    int32_t n, method;

    printf("Введите пределы интегрирования (a и b): ");
    scanf("%lf %lf", &a, &b);

    printf("Введите количество интервалов разбиения: ");
    scanf("%d", &n);

    printf("Выберите метод интегрирования:\n");
    printf("1 - Метод трапеций\n");
    printf("2 - Метод Симпсона\n");
    scanf("%d", &method);

    printf("Выберите функцию для интегрирования:\n");
    printf("1 - x^2\n");
    printf("2 - sin(x)\n");
    printf("3 - exp(x)\n");

    int32_t func_choice;
    scanf("%d", &func_choice);

    math_function func;
    switch (func_choice)
    {
        case 1:
        {
            func = square;
            break;
        }
        case 2:
        {
            func = sine;
            break;
        }
        case 3:
        {
            func = exponential;
            break;
        }
        default:
        {
            printf("Некорректный выбор функции.\n");
            return 1;
        }
    }

    double result;
    if (method == 1)
    {
        result = integrate_trapezoidal(func, a, b, n);
    }
    else if (method == 2)
    {
        result = integrate_simpson(func, a, b, n);
    }
    else
    {
        printf("Некорректный выбор метода интегрирования.\n");
        return 1;
    }

    printf("Результат интегрирования: %.6f\n", result);
}
