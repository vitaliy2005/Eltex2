#include <stdio.h>
#include <stdint.h>

uint32_t multiply_by_7(uint32_t n)
{
    return (n << 3) - n;
}

uint32_t divide_by_7(uint32_t n)
{
    unsigned int quotient = 0;
    unsigned int remainder = 0;
    unsigned int bit = 1 << 31;

    while (bit > n)
    {
        bit >>= 1;
    }

    while (bit != 0)
    {
        remainder <<= 1;
        remainder |= (n & bit) ? 1 : 0;
        n &= ~bit;


        if (remainder >= 7)
        {
            remainder -= 7;
            quotient |= bit;
        }

        bit >>= 1;
    }

    return quotient;
}

int main()
{
    uint32_t num;
    printf("Введите число: ");
    scanf("%u", &num);

    uint32_t result_mul = multiply_by_7(num);
    printf("Результат умножения %u на 7: %u\n", num, result_mul);

    uint32_t result_div = divide_by_7(num);
    printf("Результат деления %u на 7: %u\n", num, result_div);

    return 0;
}
