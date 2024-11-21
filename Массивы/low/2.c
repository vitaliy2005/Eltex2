#include <stdio.h>
#include <stdint.h>


int32_t main()
{
    int32_t SIZE;

    printf("Введите размер массива: ");
    scanf("%d", &SIZE);

    int32_t arr[SIZE];

    printf("Введите %d элементов массива: ", SIZE);
    for (int32_t i = 0; i < SIZE; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Вывод массива в обратном порядке: ");
    for (int32_t i = SIZE - 1; i >= 0; i--)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
