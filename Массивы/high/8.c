#include <stdio.h>
#include <stdlib.h>

int32_t** create_matrix(int32_t rows, int32_t cols)
{
    int32_t **matrix = (int32_t **)malloc(rows * sizeof(int32_t*));
    if (matrix == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }

    for (int32_t i = 0; i < rows; i++)
    {
        matrix[i] = (int32_t *)malloc(cols * sizeof(int32_t));
        if (matrix[i] == NULL)
        {
            printf("Ошибка выделения памяти\n");
            for (int32_t j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);

            return NULL;
        }
    }

    return matrix;
}

void fill_matrix(int32_t **matrix, int32_t rows, int32_t cols)
{
    printf("Введите элементы матрицы (%d x %d):\n", rows, cols);
    for (int32_t row = 0; row < rows; row++)
    {
        for (int32_t col = 0; col < cols; col++)
        {
            printf("Элемент [%d][%d]: ", row, col);
            scanf("%d", &matrix[row][col]);
        }
    }
}

void print_matrix(int32_t **matrix, int32_t rows, int32_t cols)
{
    printf("Матрица (%d x %d):\n", rows, cols);
    for (int32_t row = 0; row < rows; row++)
    {
        for (int32_t col = 0; col < cols; col++)
        {
            printf("%d ", matrix[row][col]);
            fflush(stdout);
        }
        printf("\n");
    }
}

void free_matrix(int32_t **matrix, int32_t rows)
{
    for (int32_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int32_t main()
{
    int32_t rows, cols;
    printf("Введите количество строк и столбцов матрицы(пример: 2 2): ");
    scanf("%d %d", &rows, &cols);

    int32_t **matrix = create_matrix(rows, cols);
    if (matrix == NULL)
    {
        return 1;
    }

    fill_matrix(matrix, rows, cols);
    print_matrix(matrix, rows, cols);
    free_matrix(matrix, rows);

    return 0;
}
