#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

const char* SERVER_IP = "192.168.141.158";

char map[10][11];

void* thread_function(void* args) {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("Error creating socket");
        return NULL;
    }

    int broadcast = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("Error setting socket options");
        return NULL;
    }

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(2345);
    recv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) < 0) {
        perror("Error binding socket");
        return NULL;
    }

    struct sockaddr_in sender_addr;
    socklen_t sender_addr_len = sizeof(sender_addr);

    while(1) {
        memset(map, 0, 110);
        int recvfrom_res = recvfrom(socket_fd, map, 110, 0, (struct sockaddr*)&sender_addr, &sender_addr_len);
        if (recvfrom_res < 0) {
            perror("Error receiving broadcast");
            continue;
        }
        printf("Printing map:\n");
        printf("%s\n", map);
    }
    
}

int main()
{

    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);

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

    char* message = "join\n";
    int send_res = send(client_socket_fd, message, strlen(message), 0);
    if (send_res < 0)
    {
        printf("Error sending message\n");
        return -1;
    }

    char recv_char;
    int recv_res = recv(client_socket_fd, &recv_char, 1, 0);
    if (recv_res < 0)
    {
        printf("Error receiving message\n");
        return -1;
    }
    printf ("Received: %c\n", recv_char);

    for(;;);
    
    close(client_socket_fd);
    return 0;
}