#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 6666
#define BUFFER_SIZE 1024

int32_t client_socket, server_socket;
int32_t close_loop = 1;


void handle_sigio(int32_t sig)
{
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
    if (client_socket < 0)
    {
        perror("Accept");
        return;
    }

    ssize_t bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_read < 0)
    {
        perror("Recv");
        if(close(client_socket) == -1)
        {
            perror("Close");
        }
        return;
    }
    char* msg = "Receive: ";
    write(STDOUT_FILENO, msg, strlen(msg));
    write(STDOUT_FILENO, buffer, bytes_read);
    write(STDOUT_FILENO, "\n", 1);
    if(close(client_socket) == -1)
    {
        perror("Close");
    }
}

void handle_sigint(int32_t sig)
{
    if (client_socket != -1)
    {
        if(close(client_socket) == -1)
        {
            perror("Close");
        }
    }
    if(close(server_socket) == -1)
    {
        perror("Close");
    }
    close_loop = 0;
}

int32_t main()
{
    struct sockaddr_in server_addr;
    struct sigaction sa, cs;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind");
        if(close(server_socket) == -1)
        {
            perror("Close");
        }
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0)
    {
        perror("Listen");
        if(close(server_socket) == -1)
        {
            perror("Close");
        }
        exit(EXIT_FAILURE);
    }


    int32_t flags = fcntl(server_socket, F_GETFL, 0);
    fcntl(server_socket, F_SETFL, flags | O_NONBLOCK | O_ASYNC);
    fcntl(server_socket, F_SETOWN, getpid());



    memset(&sa, 0, sizeof(sa));
    memset(&cs, 0, sizeof(cs));

    sa.sa_handler = handle_sigio;
    sa.sa_flags = 0;
    sigaction(SIGIO, &sa, NULL);

    cs.sa_handler = handle_sigint;
    cs.sa_flags = 0;
    sigaction(SIGINT, &cs, NULL);

    printf("Server is listening on port %d...\n", PORT);

    while (close_loop)
    {
        pause();
    }

    return 0;
}
