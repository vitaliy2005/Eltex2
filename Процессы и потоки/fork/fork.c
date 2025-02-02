#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>

int32_t main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        char *args[] = {"ls", "-l", NULL};

        if (execvp(args[0], args) < 0)
        {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int32_t status;
        if (waitpid(pid, &status, 0) < 0)
        {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status))
        {
            printf("Дочерний процесс завершился с кодом: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Дочерний процесс завершился аномально\n");
        }
    }

    return 0;
}
