#include <stdio.h>
#include <stdint.h>


uint32_t crc_find(const uint8_t *data, size_t length, uint32_t polynomial, uint32_t initial_value)
{
    uint32_t crc = initial_value;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= (data[i] << 24);

        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x80000000)
            {
                crc = (crc << 1) ^ polynomial;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

int main()
{
    uint8_t data[] = {0x31, 0x32, 0x33, 0x34, 0x35};
    size_t length = sizeof(data) / sizeof(data[0]);


    uint32_t polynomial = 0x04C11DB7;
    uint32_t initial_value = 0xFFFFFFFF;

    uint32_t crc = crc_find(data, length, polynomial, initial_value);

    printf("CRC: 0x%X\n", crc);

    return 0;
}
