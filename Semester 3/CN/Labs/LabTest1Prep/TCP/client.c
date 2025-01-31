#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const char* SERVER_IP = "192.168.13.88";

int main()
{
    int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd < 0)
    {
        printf("Error creating client socket\n");
        return -1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Error connecting to server\n");
        return -1;
    }

    printf("Connected to server %s\n", SERVER_IP);

    // ...
    
    close(client_socket_fd);
    return 0;
}