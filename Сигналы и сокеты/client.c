#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6666

int32_t main(int32_t argc, char** argv)
{
    if (argc != 2)
    {
        printf("Enter message for server\n");
        return -1;
    }

    int32_t sock = 0;
    struct sockaddr_in serv_addr;
    char *message = argv[1];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection Failed");
        return -1;
    }

    send(sock, message, strlen(message), 0);
    printf("Message sent\n");

    if(close(sock) == -1)
    {
        perror("Close");
    }

    return 0;
}
