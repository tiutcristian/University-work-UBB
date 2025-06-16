#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    const char *server_ip = "172.30.241.195";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        printf("Eroare la crearea socketului client\n");
        return -1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Eroare la conectarea la server\n");
        return -1;
    }

    
    return 0;
}