#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int32_t value;
    int32_t count;
} RLE;

RLE* compress(int32_t* arr, int32_t size, int32_t* compressed_size)
{
    if (size == 0)
    {
        *compressed_size = 0;
        return NULL;
    }

    RLE* compressed = (RLE*)malloc(size * sizeof(RLE));
    if (compressed == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }

    int32_t index = 0;
    for (int32_t i = 0; i < size; i++)
    {
        compressed[index].value = arr[i];
        compressed[index].count = 1;

        while (i + 1 < size && arr[i] == arr[i + 1])
        {
            compressed[index].count++;
            i++;
        }
        index++;
    }

    *compressed_size = index;

    return (RLE*)realloc(compressed, index * sizeof(RLE));
}

int32_t* decompress(RLE* compressed, int32_t compressed_size, int32_t* decompressed_size)
{
    if (compressed_size == 0)
    {
        *decompressed_size = 0;
        return NULL;
    }

    int32_t total_size = 0;
    for (int32_t i = 0; i < compressed_size; i++)
    {
        total_size += compressed[i].count;
    }

    int32_t* decompressed = (int32_t*)malloc(total_size * sizeof(int32_t));
    if (decompressed == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }

    int32_t index = 0;
    for (int32_t i = 0; i < compressed_size; i++)
    {
        for (int32_t j = 0; j < compressed[i].count; j++)
        {
            decompressed[index++] = compressed[i].value;
        }
    }

    *decompressed_size = total_size;

    return decompressed;
}

void print_array(int32_t* arr, int32_t size)
{
    for (int32_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int32_t main()
{
    int32_t arr[] = {4, 4, 4, 2, 2, 5, 5, 5, 5, 1};
    int32_t size = sizeof(arr) / sizeof(arr[0]);

    printf("Исходный массив: ");
    print_array(arr, size);

    int32_t compressed_size;
    RLE* compressed = compress(arr, size, &compressed_size);

    printf("Сжатый массив (значение, количество): \n");
    for (int32_t i = 0; i < compressed_size; i++)
    {
        printf("(%d, %d) ", compressed[i].value, compressed[i].count);
    }
    printf("\n");

    int32_t decompressed_size;
    int32_t* decompressed = decompress(compressed, compressed_size, &decompressed_size);

    printf("Восстановленный массив: ");
    print_array(decompressed, decompressed_size);

    free(compressed);
    free(decompressed);

    return 0;
}
