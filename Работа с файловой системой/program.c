#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Правильный запуск: %s <filename> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    const char* string_to_write = argv[2];

    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("Ошибка открытия файла для записи");
        return EXIT_FAILURE;
    }

    ssize_t bytes_written = write(fd, string_to_write, strlen(string_to_write));
    if (bytes_written == -1)
    {
        perror("Ошибка записи в файл");
        close(fd);
        return EXIT_FAILURE;
    }

    if (write(fd, "\n", 1) == -1)
    {
        perror("Ошика записи в файл");
        close(fd);
        return EXIT_FAILURE;
    }

    if (close(fd) == -1)
    {
        perror("Ошибка закрытия дискриптора");
        return EXIT_FAILURE;
    }

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Ошибка открытия файла для чтения");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    if (bytes_read == -1)
    {
        perror("Ошибка чтения файла");
        close(fd);
        return EXIT_FAILURE;
    }

    if (close(fd) == -1)
    {
        perror("Ошибка закрытия дискриптора");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
