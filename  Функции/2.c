#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int32_t IsPassOk(void);

int32_t main(void)
{
    int32_t PwStatus;
    puts("Enter password:");
    PwStatus = IsPassOk();
    if (PwStatus == 0)
    {
        printf("Bad password!\n");
        exit(1);
    }
    else
    {
        printf("Access granted!\n"); // Строка для которой нужно выяснить адрес
    }

    return 0;
}

int32_t IsPassOk(void)
{
    char Pass[12];
    fgets(Pass, 12, stdin);
    return 0 == strcmp(Pass, "test\n");
}
