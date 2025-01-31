#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

char map[10][11] = {
    "##########\n", 
    "##########\n",
    "##########\n",
    "##########\n",
    "##########\n",
    "##########\n",
    "##########\n",
    "##########\n",
    "##########\n",
    "##########\n"
};

void* serve_client(void* arg) {
    printf("Serving client\n");

    int c = *(int*)arg;

    // ...
    char join_request[100];
    int recv_res = recv(c, join_request, sizeof(join_request), 0);
    if (recv_res < 0) {
        perror("Error receiving join request");
        close(c);
        exit(0);
    }   

    int a = rand() % 10;
    int b = rand() % 10;

    char rand_char = 'a' + rand() % ('z' - 'a');

    map[a][b] = rand_char;

    // printf("asta facem local\n");
    // printf(map);
    // printf("+=======================");

    int send_res = send(c, &rand_char, 1, 0);
    if (send_res < 0) {
        perror("Error sending random character");
        close(c);
        exit(0);
    }

    close(c);
    
    return NULL;
}

void* broadcast_udp_map(void* arg) {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        perror("Socket creation failed");
        return NULL;
    }

    int broadcast = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, 
    &broadcast, sizeof(broadcast)) == -1) {
        perror("Error setting socket options");
        return NULL;
    }

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(2345);
    recv_addr.sin_addr.s_addr = inet_addr("192.168.141.255");

    while(1) {
        int sendto_res = sendto(socket_fd, map, 110, 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
        if (sendto_res < 0) {
            perror("Error sending broadcast");
            continue;
        }
        printf("Broadcast sent\n");
        sleep(5);
    }
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

    pthread_t map_broadcast;
    pthread_create(&map_broadcast, NULL, broadcast_udp_map, NULL);



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