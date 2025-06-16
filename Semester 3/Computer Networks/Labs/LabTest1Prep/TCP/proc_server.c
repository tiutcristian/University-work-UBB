#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void serve_client(int c) {
    printf("Serving client\n");

    // ...

    close(c);
    exit(0);
}

int main(int argc, char** argv) {
	
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0) {
		perror("Error creating socket\n");
		exit(-1);
	}

    struct sockaddr_in server;
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	int bind_result = bind(socket_fd, (struct sockaddr*) &server, sizeof(server));
	if(bind_result < 0) {
		perror("Bind error\n");
		exit(-1);
	}

	int listen_res = listen(socket_fd, 7);
	if(listen_res < 0){
		perror("Listening error\n");
		close(socket_fd);
		exit(-1);
	}

	while(1) {
		printf("Listening for incomming connections\n");

        struct sockaddr_in client;
	    socklen_t client_length = sizeof(client);
		int c = accept(socket_fd, (struct sockaddr*)&client, &client_length);
		if (c < 0) {
            perror("Error accepting connection\n");
            continue;
        }

        printf("Connected %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		if(fork() == 0) {
            serve_client(c);
		}
	}

	return 0;
}