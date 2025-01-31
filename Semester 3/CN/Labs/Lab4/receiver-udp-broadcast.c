#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("Error creating socket");
        return -1;
    }

    int broadcast = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("Error setting socket options");
        return -1;
    }

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(1234);
    recv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) < 0) {
        perror("Error binding socket");
        return -1;
    }

    char buffer[100];
    struct sockaddr_in sender_addr;
    socklen_t sender_addr_len = sizeof(sender_addr);
    recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&sender_addr, &sender_addr_len);
    printf("Received: %s\n", buffer);
}