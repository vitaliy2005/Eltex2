#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

uint64_t result1 = 0;
uint64_t result2 = 0;
uint64_t result3 = 0;

typedef struct
{
    int start;
    int end;
} Range_t;

void* calculate_sum_of_squares(void* arg)
{
    Range_t* range = (Range_t*)arg;
    uint64_t sum = 0;

    for (int i = range->start; i <= range->end; i++)
    {
        sum += (long long)i * i;
    }

    uint64_t* result = malloc(sizeof(uint64_t));
    *result = sum;
    pthread_exit(result);
}

int32_t main()
{
    int32_t N = 1000;
    pthread_t thread1, thread2, thread3;
    Range_t range1, range2, range3;

    range1.start = 1;
    range1.end = N / 3;

    range2.start = N / 3 + 1;
    range2.end = 2 * N / 3;

    range3.start = 2 * N / 3 + 1;
    range3.end = N;

    pthread_create(&thread1, NULL, calculate_sum_of_squares, &range1);
    pthread_create(&thread2, NULL, calculate_sum_of_squares, &range2);
    pthread_create(&thread3, NULL, calculate_sum_of_squares, &range3);

    uint64_t* sum1;
    uint64_t* sum2;
    uint64_t* sum3;

    pthread_join(thread1, (void**)&sum1);
    pthread_join(thread2, (void**)&sum2);
    pthread_join(thread3, (void**)&sum3);

    uint64_t total_sum = *sum1 + *sum2 + *sum3;

    free(sum1);
    free(sum2);
    free(sum3);

    printf("Сумма квадратов чисел от 1 до %d: %ld\n", N, total_sum);

    return 0;
}
