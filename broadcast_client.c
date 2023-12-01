#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
    int clientsock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr, clientaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9000);
    servaddr.sin_addr.s_addr = inet_addr("10.0.2.255");
    int reuse = 1;
    setsockopt(clientsock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    bind(clientsock, (struct sockaddr *)&servaddr, sizeof(servaddr));
    char rcvmsg[100];
    bzero(rcvmsg, 100);
    int cli = sizeof(clientaddr);
    while (1)
    {
        recvfrom(clientsock, rcvmsg, 100, 0, (struct sockaddr *)&clientaddr, &cli);
        printf("message received: %s", rcvmsg);
    }
}