#include <stdio.h>
#include <stdint.h>


int32_t main()
{
    int32_t SIZE;

    printf("Введите размер матрицы: ");
    scanf("%d", &SIZE);

    int32_t matrix[SIZE][SIZE];

    for (int32_t i = 0; i < SIZE; i++)
    {
        for (int32_t j = 0; j < SIZE; j++)
        {
                matrix[i][j] = (j >= i) ? 1 : 0;
        }
    }

    printf("Матрица:\n");
    for (int32_t i = 0; i < SIZE; i++)
    {
        for (int32_t j = 0; j < SIZE; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
