#include <stdint.h>
#include <stdio.h>

int32_t parity(uint32_t num)
{
    uint32_t count = 0;

    while (num > 0)
    {
        count += num & 1;
        num >>= 1;
    }

    return (count % 2 == 0) ? 1 : 0;
}

int32_t main()
{
    uint32_t number;

    printf("Введите беззнаковое целое число: ");
    scanf("%u", &number);

    if (parity(number))
    {
        printf("Количество установленных битов четное.\n");
    }
    else
    {
        printf("Количество установленных битов нечетное.\n");
    }

    return 0;
}
