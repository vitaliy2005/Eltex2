#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "mod_kernel.h"

int32_t main(int32_t argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: ./main text");
        return -1;
    }

    int32_t fd = open("/dev/custom_device", O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open the device");
        return -1;
    }

    int32_t state = 1;
    ioctl(fd, IOCTL_SET_STATE, &state);

    ioctl(fd, IOCTL_GET_STATE, &state);
    printf("Current state: %d\n", state);

    write(fd, argv[1], strlen(argv[1]));

    char read_buffer[20];
    read(fd, read_buffer, 20);
    printf("Read from device: %s\n", read_buffer);

    close(fd);
    return 0;
}
