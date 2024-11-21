#include <stdio.h>
#include <stdint.h>

void print_array_uint8(uint8_t* arr, const char* message)
{
    printf("%s", message);
    for (int i = 0; i < 8; i++)
    {
        printf("0x%X ", arr[i]);
    }
    printf("\n");
}

uint64_t compress_array_uint8(uint8_t* original)
{
    uint64_t compressed = 0;
    for (int32_t i = 0; i < 8; i++)
    {
        compressed |= ((uint64_t)original[8-i-1] << (i * 8));
    }
    return compressed;
}

void decompress_array_uint8(uint64_t compressed, uint8_t* decompressed)
{
    for (int32_t i = 0; i < 8; i++)
    {
        decompressed[8-i-1] = (compressed >> (i*8)) & 0xFF;
    }
}

int32_t main()
{
    uint8_t original[8] = {0x11, 0x22, 0x33, 0x44, 0xAA, 0xBB, 0xCC, 0xFF};
    uint8_t decompressed[8];
    uint64_t compressed;

    print_array_uint8(original, "Исходный массив: ");

    compressed = compress_array_uint8(original);
    printf("Сжатое значение: 0x%016lX\n", compressed);

    decompress_array_uint8(compressed, decompressed);
    print_array_uint8(decompressed, "Восстановленный массив: ");
}
