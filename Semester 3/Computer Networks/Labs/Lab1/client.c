#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char** argv) {

	struct sockaddr_in server;
	
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_fd == -1) {
		printf("socket error\n");
		return -1;		
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	int bind_result = bind(socket_fd, (struct sockaddr*)&server, sizeof(server));

	if (bind_result == -1) {
		printf("bind error\n");
		return -1;
	}

	return 0;
}
