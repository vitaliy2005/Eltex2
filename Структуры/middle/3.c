#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE_BUFFER 1024
#define MAX_ENTRIES 200


typedef struct
{
    char timestamp[20];
    char event[50];
    uint32_t severity;
}Log_entry_t;

int32_t read_event_log(const char* filename, Log_entry_t* log);
int32_t save_event_log(const char* filename, Log_entry_t* log, uint32_t severity);


int32_t read_event_log(const char* filename, Log_entry_t* log)
{
    int32_t count = 0;

    int32_t fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        perror("Не удалось открыть файл");
        return -1;
    }

    char buffer[SIZE_BUFFER] = {0};
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1)
    {
        perror("Не удалось прочитать файл");
        return -1;
    }

    close(fd);

    char* line = strtok(buffer, "\n");
    while (line && count++ < MAX_ENTRIES)
    {
        if(sscanf(line, "%19s %49s %du", log->timestamp, log->event, &log->severity) != 3)
        {
            perror("Некорректные данные");
            return -1;
        }

        line = strtok(NULL, "\n");
    }

    return 0;
}

int32_t save_event_log(const char* filename, Log_entry_t* log, uint32_t severity)
{
    int32_t fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if(fd == -1)
    {
        perror("Ошибка открытия файла");
        return -1;
    }

    char buffer[SIZE_BUFFER] = {0};
    for (size_t i = 0; (i < MAX_ENTRIES) && (log[i].timestamp[0] != '\0'); i++)
    {
        if (log->severity >= severity)
        {
            int32_t len = snprintf(buffer, sizeof(buffer), "%s %s %u\n", log->timestamp, log->event, log->severity);
            if(write(fd, buffer, len) != len)
            {
                perror("Не удалось записать файл");
                close(fd);
                return -1;
            }
        }
    }

    close(fd);

    return 0;
}


int32_t main()
{
    Log_entry_t entries[MAX_ENTRIES] = {0};
    const char *input_file = "log.txt";
    const char *output_file = "filtered_log.txt";

    int32_t entry_сount = read_event_log(input_file, entries);
    if (entry_сount == -1)
    {
        return 1;
    }

    printf("Записи прочитаны из файла %s.\n", input_file);

    int min_severity = 3;
    if (save_event_log(output_file, entries, min_severity) == -1)
    {
        return 1;
    }

    printf("Отфильтрованные записи записаны в файл %s.\n", output_file);
}
