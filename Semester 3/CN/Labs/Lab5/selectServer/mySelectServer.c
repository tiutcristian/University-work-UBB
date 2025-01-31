#include <sys/select.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    fd_set master;
    fd_set read_fds;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("Error creating socket");
        exit(-1);
    }

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    struct sockaddr_in server_info;
    memset(&server_info, 0, sizeof(struct sockaddr_in));
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1234);
    server_info.sin_addr.s_addr = INADDR_ANY;

    int result_bind = bind(socket_fd, (const struct sockaddr*)&server_info, sizeof(server_info));
    if (result_bind == -1) {
        perror("Error binding socket");
        exit(-2);
    }

    int result_listen = listen(socket_fd, 7);
    if (result_listen == -1) {
        perror("Error listening on socket");
        exit(-3);
    }

    FD_SET(socket_fd, &master);
    int fdmax = socket_fd;

    struct sockaddr_in client_info;
    socklen_t client_info_len;

    for(;;) {
        printf("Waiting for clients...\n");

        read_fds = master;
        int result_select = select(fdmax + 1, &read_fds, NULL, NULL, NULL);
        if (result_select == -1) {
            perror("Error in select");
            exit(-4);
        }

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == socket_fd) {
                    int client_fd = accept(i, (struct sockaddr*)&client_info, &client_info_len);
                    if (client_fd == -1) {
                        perror("Error accepting");
                    } else {
                        FD_SET(client_fd, &master);
                        if (client_fd > fdmax) {
                            fdmax = client_fd;
                        }
                        printf("Client connected with IP: %s and port: %d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
                        close(client_fd);
                        FD_CLR(client_fd, &master);
                    }
                }
            }
        }
    }

    return 0;
}