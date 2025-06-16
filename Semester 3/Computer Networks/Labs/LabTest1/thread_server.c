#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


struct client_info{
    int client_fd;
    struct sockaddr_in client;
};

void* handle_client(void* args){

	struct client_info cl_info = *((struct client_info*)args);
	int clientfd = cl_info.client_fd;
	struct sockaddr_in client = cl_info.client;
	printf("Conneccted %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
	close(clientfd);
    return NULL;
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

    int max_threads = 8;
    pthread_t threads[max_threads];
    int num_of_threads = 0;


	while(1){

		printf("Waiting for users\n");
		clientfd = accept(socket_fd, (struct sockaddr*)&client, &client_length);

        struct client_info* cli_info = (struct client_info*)malloc(sizeof(struct client_info));
        cli_info->client_fd = clientfd;
        cli_info->client = client;
        pthread_create(&threads[num_of_threads++], 0, handle_client, (void*)cli_info);
		printf("num_of_threads: %d\n", num_of_threads);
		
		if (num_of_threads == max_threads){
			num_of_threads = 0;
			for(int i = 0; i < max_threads; i++){
				pthread_join(threads[i], NULL);
			}
		}

	}

	return 0;
}
