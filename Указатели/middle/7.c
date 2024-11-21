#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 3
#define N 4


int32_t main()
{
    int32_t arr[M][N];
    int32_t row_sums[M] = {0};
    int32_t col_sums[N] = {0};

    srand(time(NULL));

    printf("Массив:\n");
    for (int32_t i = 0; i < M; i++)
    {
        for (int32_t j = 0; j < N; j++)
        {
            *(*(arr + i) + j) = rand() % 10;
            printf("%2d ", *(*(arr + i) + j));
        }
        printf("\n");
    }

    for (int32_t i = 0; i < M; i++)
    {
        for (int32_t j = 0; j < N; j++)
        {
            row_sums[i] += *(*(arr + i) + j);
        }
    }

    for (int32_t j = 0; j < N; j++)
    {
        for (int32_t i = 0; i < M; i++)
        {
            col_sums[j] += *(*(arr + i) + j);
        }
    }

    printf("\nСумма по строкам:\n");
    for (int32_t i = 0; i < M; i++)
    {
        printf("Строка %d: %d\n", i, row_sums[i]);
    }

    printf("\nСумма по столбцам:\n");
    for (int32_t j = 0; j < N; j++)
    {
        printf("Столбец %d: %d\n", j, col_sums[j]);
    }
}
