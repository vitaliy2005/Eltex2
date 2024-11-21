#include <stdio.h>
#include <stdint.h>

int32_t main()
{
    uint32_t N;
    printf("Введите положительное целое число: ");
    scanf("%u", &N);

    int count = 0;
    while (N > 0)
    {
        if (N & 1)
            count++;
        N >>= 1;
    }

    printf("Количество единиц в двоичном представлении: %d\n", count);
}
