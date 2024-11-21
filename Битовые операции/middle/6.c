#include <stdio.h>
#include <stdint.h>

uint32_t set_bit(uint32_t num, int bit)
{
    return num | (1 << (bit - 1));
}

uint32_t clear_bit(uint32_t num, int bit)
{
    return num & ~(1 << (bit - 1));
}

uint32_t toggle_bit(uint32_t num, int bit)
{
    return num ^ (1 << (bit - 1));
}

void print_bin(uint32_t num)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
        if (i > 0 && i % 8 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");
}

int main()
{
    uint32_t test = 0b10101010101010101010101010101010;
    uint32_t test_2 = 0b11111111111111111111111111111111;
    uint32_t test_3 = 0b00000000000000000000000000000000;

    int bit_position;

    printf("Исходные числа:\n");
    print_bin(test);
    print_bin(test_2);
    print_bin(test_3);

    bit_position = 5;
    test = set_bit(test, bit_position);
    test_2 = set_bit(test_2, bit_position);
    test_3 = set_bit(test_3, bit_position);

    printf("После установки бита %d:\n", bit_position);
    print_bin(test);
    print_bin(test_2);
    print_bin(test_3);

    bit_position = 2;
    test = clear_bit(test, bit_position);
    test_2 = clear_bit(test_2, bit_position);
    test_3 = clear_bit(test_3, bit_position);

    printf("После сброса бита %d:\n", bit_position);
    print_bin(test);
    print_bin(test_2);
    print_bin(test_3);

    bit_position = 3;
    test = toggle_bit(test, bit_position);
    test_2 = toggle_bit(test_2, bit_position);
    test_3 = toggle_bit(test_3, bit_position);

    printf("После инвертирования бита %d:\n", bit_position);
    print_bin(test);
    print_bin(test_2);
    print_bin(test_3);

    return 0;
}
