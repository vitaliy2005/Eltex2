#include <stdio.h>
#include <stdint.h>

int32_t main()
{
    int32_t N;

    printf("Введите размер матрицы: ");
    scanf("%d", &N);

    int32_t matrix[N][N];

    int32_t left = 0, right = N - 1, top = 0, bottom = N - 1;
    int32_t num = 1;

    while (num <= N * N)
    {
        for (int32_t i = left; i <= right; i++)
        {
            matrix[top][i] = num++;
        }
        top++;

        for (int32_t i = top; i <= bottom; i++)
        {
            matrix[i][right] = num++;
        }
        right--;

        if (top <= bottom)
        {
            for (int32_t i = right; i >= left; i--)
            {
                matrix[bottom][i] = num++;
            }
            bottom--;
        }

        if (left <= right)
        {
            for (int32_t i = bottom; i >= top; i--)
            {
                matrix[i][left] = num++;
            }
            left++;
        }
    }

    printf("Матрица, заполненная улиткой:\n");
    for (int32_t row = 0; row < N; row++)
    {
        for (int32_t col = 0; col < N; col++)
        {
            printf("%2d ", matrix[row][col]);
        }
        printf("\n");
    }

    return 0;
}
