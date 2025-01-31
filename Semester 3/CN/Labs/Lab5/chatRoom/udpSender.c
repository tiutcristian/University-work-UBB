#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        perror("Socket creation failed");
        return -1;
    }

    char input_buffer[100];
    char output_buffer[100] = "Hello, World!";
    strcpy(output_buffer, "Sunt eu, un haiduc!");

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(1234);
    recv_addr.sin_addr.s_addr = inet_addr("172.30.248.251");

    struct sockaddr_in sender_addr;

    while(1) {
        sendto(socket_fd, output_buffer, sizeof(output_buffer), 0,
        (struct sockaddr*)&recv_addr, sizeof(recv_addr));
        sleep(2);
        recvfrom(socket_fd, input_buffer, sizeof(input_buffer), 0, 
        (struct sockaddr*)&sender_addr, &(socklen_t){sizeof(sender_addr)});
    }

    return 0;
}