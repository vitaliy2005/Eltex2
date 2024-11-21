#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define SIZE_STR 100

char* find_substr(char* str, char* substr)
{
    int32_t len_substr = strlen(substr);
    int32_t len_str = strlen(str);

    if (len_substr == 0 || len_str < len_substr)
        return NULL;

    for (int32_t i = 0; i < len_str - len_substr; i++)
    {
        int32_t flag = true;
        int32_t index_substr = 0;
        for (int32_t j = i; j < (len_substr+i); j++)
        {
            if (str[j] != substr[index_substr++])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            return str+i;
    }

    return NULL;
}


int32_t main()
{
    char str[SIZE_STR];
    char substr[SIZE_STR];
    char* p_substr = NULL;

    printf("Введите строку: ");
    fgets(str, SIZE_STR, stdin);
    str[strcspn(str, "\n")] = '\0';

    printf("Введите подстроку: ");
    fgets(substr, SIZE_STR, stdin);
    substr[strcspn(substr, "\n")] = '\0';

    p_substr = find_substr(str, substr);
    if (p_substr)
        printf("Начало подстроки: %s\n", p_substr);
    else
        printf("Отсутствует искомая подстрока\n");
}
