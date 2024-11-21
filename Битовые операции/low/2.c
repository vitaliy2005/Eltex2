#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE_INT 32

void binary_rep(int32_t num, char* bin_n)
{
    for(int32_t i = 0; i < SIZE_INT; i++)
        bin_n[SIZE_INT - i - 1] = (num & (1 << i)) ? '1' : '0';
}

void print_num(char* bin_n)
{
    for(int32_t i = 0; i < SIZE_INT; i++)
    {
        if(i > 0 && i % 8 == 0)
            printf(" ");
        printf("%c", bin_n[i]);
    }
    printf("\n");
}


int32_t main()
{
    int32_t N;
    printf("Введите число:");
    scanf("%d", &N);

    int32_t inverted = ~N;
    char bin_n[SIZE_INT + 1];
    bin_n[SIZE_INT] = '\0';

    binary_rep(N, bin_n);
    print_num(bin_n);

    binary_rep(inverted+1, bin_n);
    print_num(bin_n);
}
