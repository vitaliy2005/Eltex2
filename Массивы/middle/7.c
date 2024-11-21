#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE_ARR 12


void merge_sort(int16_t* arr, int16_t size_arr)
{
    if (size_arr <= 1)
        return;

    int16_t* buffer = malloc(sizeof(int16_t) * size_arr);
    if (buffer == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return;
    }

    int16_t middle = size_arr / 2;
    int16_t* left = arr;
    int16_t* right = arr + middle;
    int16_t left_size = middle;
    int16_t right_size = size_arr - middle;

    merge_sort(left, left_size);
    merge_sort(right, right_size);

    int16_t left_i = 0, right_i = 0, buffer_i = 0;
    while( (left_i < left_size) && (right_i < right_size) )
    {
        if (left[left_i] <= right[right_i] )
            buffer[buffer_i++] = left[left_i++];
        else
            buffer[buffer_i++] = right[right_i++];
    }

    while (left_i < left_size)
        buffer[buffer_i++] = left[left_i++];

    while (right_i < right_size)
        buffer[buffer_i++] = right[right_i++];

    for (int16_t i = 0; i < size_arr; i++)
    {
        arr[i] = buffer[i];
    }

    free(buffer);
}


int32_t binary_search(int16_t* nums, int16_t num, int16_t low, int16_t high)
{

    if (low <= high)
    {
        int16_t middle = low + (high - low) / 2;

        if(nums[middle] < num)
        {
            low = middle + 1;
            return binary_search(nums, num, low, high);
        }
        else if(nums[middle] > num)
        {
            high = middle - 1;
            return binary_search(nums, num, low, high);
        }
        else if(nums[middle] == num)
        {
            return middle;
        }
    }

    return -1;
}


void print_array(int16_t* arr)
{
    for (int16_t i = 0; i < SIZE_ARR; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int32_t main()
{
	int16_t nums[SIZE_ARR] = {10, 8, 7, 9, 5, 4, 2, 3, 1, 6, 10, 10};

	printf("Изначальный массив для поиска числа: ");
	print_array(nums);

	merge_sort(nums, SIZE_ARR);
	printf("Отсортированный массив для поиска числа: ");
	print_array(nums);

	printf("Введите число для поиска: ");
	int16_t num;
	scanf("%hd", &num);
	int16_t index = binary_search(nums, num, 0, SIZE_ARR);
	if(index != -1)
	{
	   printf("индекс числа: %hd\n", index);
	}
	else
	{
	   printf("Элемент не найден\n");
	}
}
