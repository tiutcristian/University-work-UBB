#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct client_info {
    int clientfd;
    struct sockaddr_in client;
};

void* handle_client(void* arg) {
    struct client_info client_info = *(struct client_info*)arg;
    int clientfd = client_info.clientfd;
    struct sockaddr_in client = client_info.client;
    printf("Conneccted %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    return 0;
}

int main(int argc, char** argv){

	struct sockaddr_in server;
	

	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd == -1){
		printf("socket error\n");
		return -1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	int bind_result = bind(socket_fd, (struct sockaddr*) &server, sizeof(server));

	if(bind_result == -1){
		printf("bind error\n");
		return -1;
	}

	int listen_res = listen(socket_fd, 7);

	if(listen_res == -1){
		printf("listening error\n");
		close(socket_fd);
		return -1;
	}


	struct sockaddr_in client;
	socklen_t client_length;
	int clientfd;

    int maximum_no_of_threads = 8;
    pthread_t threads[maximum_no_of_threads];
    int num_of_threads = 0;

	while(1){
		printf("Waiting for users\n");
		clientfd = accept(socket_fd, (struct sockaddr*)&client, &client_length);
        struct client_info* client_info = (struct client_info*)malloc(sizeof(struct client_info));
        client_info->clientfd = clientfd;
        client_info->client = client;
        pthread_create(&threads[num_of_threads++], 0, handle_client, client_info);

        
	
		close(clientfd);

	}

	return 0;
}