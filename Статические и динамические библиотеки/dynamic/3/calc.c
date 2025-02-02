#include "calc.h"


int32_t add(int32_t a, int32_t b)
{
    return a + b;
}

int32_t subtract(int32_t a, int32_t b)
{
    return a - b;
}

int32_t multiply(int32_t a, int32_t b)
{
    return a * b;
}

double divide(double a, double b)
{
    if (b == 0)
    {
        divide_null();
        return 0;
    }

    return a / b;
}


static void divide_null()
{
    printf("Деление на ноль невозможно\n");
}
