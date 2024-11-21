#include <stdio.h>
#include <stdint.h>
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
    uint32_t num, new_byte;
    char bin_n[SIZE_INT+1];
    bin_n[SIZE_INT] = '\0';
    printf("Введите положительное целое число: ");
    scanf("%u", &num);

    printf("Введите новое значение для третьего байта (0-255): ");
    scanf("%u", &new_byte);

    if (new_byte > 255)
    {
        printf("Ошибка: значение должно быть в диапазоне от 0 до 255.\n");
        return 1;
    }
    binary_rep(new_byte, bin_n);
    printf("Новый 3-ий байт:");
    print_num(bin_n);


    binary_rep(num, bin_n);
    printf("Число до измененния в бинарном виде:");
    print_num(bin_n);

    num = (num & 0xFF00FFFF) | (new_byte << 16);
    binary_rep(num, bin_n);
    printf("Число после изменения третьего байта:");
    print_num(bin_n);

}
