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

    char input_buffer[100];
    char output_buffer[100] = "Hello, World!";
    strcpy(output_buffer, "Sunt eu, un haiduc!");

    struct sockaddr_in sender_addr;

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(1234);
    recv_addr.sin_addr.s_addr = inet_addr("172.30.248.251");

    while (1) {
        // to be done
    }
}