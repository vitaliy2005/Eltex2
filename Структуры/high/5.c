#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>


typedef struct
{
    int intData;
    float floatData;
    char strData[50];
} Data_packet_t;

uint32_t get_checksum(void* data, size_t len)
{
    uint32_t checksum = 0;
    uint8_t* buffer = (uint8_t*)data;

    for (int8_t i = 0; i < len; i++)
    {
        checksum += buffer[i];
    }

    return checksum;
}

uint8_t* serialize_data_packet(Data_packet_t* data, size_t* size)
{
    *size = sizeof(*data);
    uint8_t* buffer = malloc(sizeof(uint8_t) * (*size) + sizeof(uint8_t));
    if(!buffer)
    {
        perror("Не удалось выделить память");
        return NULL;
    }

    memcpy(buffer, data, *size);

    uint32_t checksum = get_checksum(buffer, *size);

    memcpy(buffer + (*size), &checksum, sizeof(checksum));

    *size += sizeof(uint32_t);

    return buffer;
}

Data_packet_t* deserialize_data_packet(uint8_t* data)
{
    Data_packet_t* deserialize_data = malloc(sizeof(Data_packet_t));
    if(!deserialize_data)
    {
        perror("Не удалось выделить память");
        return NULL;
    }

    memcpy(deserialize_data, data, sizeof(Data_packet_t));

    uint32_t* checksum;
    checksum = (uint32_t*)(data + sizeof(Data_packet_t));

    if(*checksum != get_checksum(deserialize_data, sizeof(Data_packet_t)))
    {
        printf("Ошибка: контрольная сумма не совпадает!\n");
        return NULL;
    }

    return deserialize_data;
}


void printDataPacket(Data_packet_t* packet)
{
    printf("intData: %d\n", packet->intData);
    printf("floatData: %.2f\n", packet->floatData);
    printf("strData: %s\n", packet->strData);
}

int main() {
    Data_packet_t originalPacket = {42, 3.14f, "Hello, world!"};

    size_t serialized_size;
    unsigned char *serialized_data = serialize_data_packet(&originalPacket, &serialized_size);

    if (!serialized_data)
    {
        return -1;
    }

    printf("Сериализованные данные: \n");
    for (size_t i = 0; i < serialized_size; i++)
    {
        printf("%02x ", serialized_data[i]);
    }
    printf("\n");


    Data_packet_t* deserialized_data = deserialize_data_packet(serialized_data);
    if (!deserialized_data)
    {
        free(serialized_data);
        return -1;
    }

    printf("\nДесериализованные данные:\n");
    printDataPacket(deserialized_data);

    free(serialized_data);
    free(deserialized_data);
}
