#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int sock, length, fromlen, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        error("Error opening socket");
    }

    length = sizeof(server);
    bzero(&server, length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1234);

    if (bind(sock, (struct sockaddr *)&server, length) < 0) {
        error("Binding error");
    }

    fromlen = sizeof(struct sockaddr_in);
    while (1) {
        n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, (socklen_t *)&fromlen);
        if (n < 0) {
            error("Error in recvfrom");
        }
            
        write(1, "Received a datagram: ", 21);
        write(1, buf, n);

        n = sendto(sock, "Got your message\n", 17, 0, (struct sockaddr *)&from, fromlen);
        if (n < 0) {
            error("Error in sendto");
        }
    }
}