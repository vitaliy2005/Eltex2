#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <time.h>

#define cols 4
#define rows 4

void printf_matrix(int32_t* matrix)
{
    for (int32_t row = 0; row < rows; row++)
    {
        for (int32_t col = 0; col < cols; col++)
        {
            printf("%d ", matrix[cols * row + col]);
        }
        printf("\n");
    }
    printf("\n");
}

int32_t main()
{

    int32_t* matrix = malloc(sizeof(int32_t) * cols * rows);
    if (matrix == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return 0;
    }

    srand(time(NULL));

    for (int32_t row = 0; row < rows; row++)
    {
        for (int32_t col = 0; col < cols; col++)
        {
            matrix[cols * row + col] = rand() % 2;
        }
    }
    printf_matrix(matrix);

    for (int32_t row = 0; row < rows; row++)
    {
        for (int32_t col = row+1; col < cols; col++)
        {
            matrix[cols * row + col] ^= matrix[rows*col+row];
            matrix[rows*col+row] ^= matrix[cols * row + col];
            matrix[cols * row + col] ^= matrix[rows*col+row];
        }
    }
    printf_matrix(matrix);

    free(matrix);
}
