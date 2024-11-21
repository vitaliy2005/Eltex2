#include <stdio.h>
#include <stdint.h>


int32_t main()
{
    int32_t rows, cols;

    printf("Введите количество строк для квадратной матрицы: ");
    scanf("%d", &rows);

    cols = rows;
    const int32_t SIZE = rows * rows;
    int32_t matrix[SIZE];

    for (int32_t index = 1; index <= SIZE; index++)
        matrix[index-1] = index;

    for (int32_t row = 0; row < rows; row++)
    {
        for (int32_t col = 0; col < cols; col++)
        {
           printf("%d ", matrix[cols * row + col]);
           fflush(stdout);
        }
        printf("\n");
    }
}
