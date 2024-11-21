#include <stdint.h>
#include <stdio.h>


int32_t main()
{
    float x = 5.0;
    printf("x = %f, ", x);
    float y = 6.0;
    printf("y = %f\n", y);
    float *xp = &y;
    float *yp = &y;
    printf("Результат: %f\n", *xp + *yp);
}
