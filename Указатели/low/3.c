#include <stdio.h>
#include <stdint.h>


int main()
{
    int32_t arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int32_t* ptr = arr;

    printf("Элементы массива: ");
    for (int32_t i = 0; i < 10; i++)
    {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
}
