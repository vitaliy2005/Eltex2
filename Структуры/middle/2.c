#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROOMS 5


typedef struct
{
    size_t id;
    bool state;
    size_t brightness;
}Light_t;

typedef struct
{
    char* name_room;
    Light_t* lights;
    size_t num_lamps;
}Room_t;


void init_room(Room_t* room, const char* name_room, size_t num_lamps)
{
        room->lights = malloc(sizeof(Light_t) * num_lamps);
        if (!room->lights)
        {
            perror("Ошибка выделения памяти для светильников");
            return;
        }
        room->num_lamps = num_lamps;

        for (size_t i = 0; i < num_lamps; i++)
        {
            room->lights[i].id = i;
            room->lights[i].state = false;
            room->lights[i].brightness = 0;
        }

        room->name_room = strdup(name_room);
        if (!room->name_room)
        {
            free(room->lights);
            perror("Ошибка выделения памяти для имени комнаты");
            return;
        }
}

void toggle_lamps(Room_t* room, bool state)
{
    for (size_t i = 0; i < room->num_lamps; i++)
    {
        room->lights[i].state = state;
        if(room->lights[i].brightness == 0 && state)
        {
            room->lights[i].brightness = 75;
        }

        if(room->lights[i].brightness > 0 && !state)
        {
            room->lights[i].brightness = 0;
        }
    }
}

void set_brightness(Room_t* room, size_t lamp_id, size_t brightness)
{
    if (lamp_id < 0 || lamp_id > room->num_lamps-1)
    {
        printf("Ошибка: Неверный ID светильника.\n");
        return;
    }

    if (brightness < 0 || brightness > 100)
    {
        printf("Ошибка: Неверная мощность свечения светильника.\n");
        return;
    }

    room->lights[lamp_id].brightness = brightness;
    room->lights[lamp_id].state = (brightness > 0) ? true : false;
}

void print_lamp_stat(Room_t* rooms)
{
    for (int32_t i = 0; i < MAX_ROOMS; i++)
    {
        if (rooms[i].name_room == NULL) break;

        printf("Комната: %s\n", rooms[i].name_room);
        for (int j = 0; j < rooms[i].num_lamps; j++)
        {
            Light_t light = rooms[i].lights[j];
            printf("  Светильник %ld: состояние=%s, яркость=%ld\n", light.id, light.state ? "включен" : "выключен", light.brightness);
        }
    }
}

void free_rooms(Room_t* house)
{
    for(int32_t i = 0; i < MAX_ROOMS; i++)
    {
        free(house[i].name_room);
        free(house[i].lights);
    }
}



int32_t main()
{
    Room_t house[MAX_ROOMS] = {NULL};
    init_room(&house[0], "Гостинная", 5);
    init_room(&house[1], "Спальня", 2);
    printf("%s\n",house[1].name_room);

    print_lamp_stat(house);

    set_brightness(&house[1], 1, 50);
    toggle_lamps(&house[0], true);
    print_lamp_stat(house);

    toggle_lamps(&house[0], false);
    print_lamp_stat(house);

    set_brightness(&house[1], 0, 1);
    print_lamp_stat(house);

    free_rooms(house);
}
