#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint16_t sensors;
} Status_flags_t;

void set_sensor_status(Status_flags_t* status, uint16_t index, bool state)
{
    if (index >= 16)
    {
        printf("Ошибка: неверный индекс датчика.\n");
        return;
    }

    uint16_t offset = 1 << index;

    status->sensors = state ? status->sensors | offset : status->sensors & offset;

}

int check_sensor_state(Status_flags_t* status, uint32_t index)
{
    if (index >= 16)
    {
        printf("Ошибка: неверный индекс датчика.\n");
        return -1;
    }

    return (status->sensors >> index) & 1;
}

void print_system_status(Status_flags_t* status)
{
    printf("Состояние системы:\n");
    for (int i = 0; i < 16; i++)
    {
        printf("Датчик %d: %s\n", i, (status->sensors >> i) & 1 ? "Авария" : "Норма");
    }
}

int32_t main()
{
    Status_flags_t status = {0};

    set_sensor_status(&status, 3, 1);
    set_sensor_status(&status, 7, 1);
    set_sensor_status(&status, 12, 1);

    printf("Состояние датчика 3: %s\n", check_sensor_state(&status, 3) ? "Авария" : "Норма");
    printf("Состояние датчика 7: %s\n", check_sensor_state(&status, 7) ? "Авария" : "Норма");
    printf("Состояние датчика 5: %s\n", check_sensor_state(&status, 5) ? "Авария" : "Норма");

    print_system_status(&status);5
}
