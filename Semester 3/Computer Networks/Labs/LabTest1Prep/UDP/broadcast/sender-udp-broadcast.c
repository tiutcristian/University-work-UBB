#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        perror("Socket creation failed");
        return -1;
    }

    int broadcast = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, 
    &broadcast, sizeof(broadcast)) == -1) {
        perror("Error setting socket options");
        return -1;
    }

    char buffer[100] = "Hello, World!";

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(1234);
    recv_addr.sin_addr.s_addr = inet_addr("172.30.255.255");

    while(1) {
        sendto(socket_fd, buffer, sizeof(buffer) + 1, 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
    }

    return 0;
}