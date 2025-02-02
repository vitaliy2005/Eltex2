#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int32_t main()
{
    void *handle;
    int32_t (*add)(int32_t, int32_t);
    char *error;

    handle = dlopen("./libapp.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    add = (int32_t (*)(int32_t, int32_t)) dlsym(handle, "add");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "Ошибка получения адреса функции: %s\n", error);
        dlclose(handle);
        return 1;
    }

    int32_t a = 10, b = 5;
    int32_t result = add(a, b);
    printf("Результат сложения 10 и 5 == %d\n", result);

    dlclose(handle);
    return 0;
}
