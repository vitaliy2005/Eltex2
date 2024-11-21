#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE_INT 32


int32_t main()
{
    int32_t N;
    printf("Введите число: ");
    scanf("%d", &N);

    char bin_n[SIZE_INT + 1];
    bin_n[SIZE_INT] = '\0';

    for(int32_t i = 0; i < SIZE_INT; i++)
        bin_n[SIZE_INT - i - 1] = (N & (1 << i)) ? '1' : '0';

    for(int32_t i = 0; i < SIZE_INT; i++)
    {
        if(i > 0 && i % 8 == 0)
            printf(" ");
        printf("%c", bin_n[i]);
    }
    printf("\n");
}
