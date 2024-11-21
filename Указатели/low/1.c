#include <stdio.h>
#include <stdint.h>


int32_t main()
{
    int32_t num;

    printf("Введите число: ");
    scanf("%d", &num);
    printf("%b\n", num);

    int8_t* pnum = (int8_t*)&num;

    printf("Введите новый байт: ");
    scanf("%hhd", (pnum+2));
    printf("%b\n", num);
}
