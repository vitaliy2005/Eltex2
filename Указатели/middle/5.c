#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define SIZE_STR 100


void reverse_string(char *str)
{
    if (str == NULL)
        return;

    char *start = str;
    char *end = str;

    while (*end)
    {
        end++;
    }
    end--;

    while (start < end)
    {
        *start = *start ^ *end;
        *end = *start ^ *end;
        *start = *start ^ *end;

        start++;
        end--;
    }
}

int32_t main()
{
    char str[SIZE_STR];

    printf("Введите строку: ");
    fgets(str, SIZE_STR, stdin);
    str[strcspn(str, "\n")] = '\0';

    printf("Исходная строка: %s\n", str);

    reverse_string(str);

    printf("Перевернутая строка: %s\n", str);
}
