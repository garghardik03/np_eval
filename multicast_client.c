#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main() 
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int reuse = 1; // Set the SO_REUSEADDR option
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    struct sockaddr_in local_addr;
    bzero(&local_addr, sizeof(local_addr))
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY; // Receive datagrams addressed to the multicast group
    local_addr.sin_port = htons(5000); 
    bind(sock, (struct sockaddr*)&local_addr, sizeof(local_addr));
    struct ip_mreq multicast_request;
    multicast_request.imr_multiaddr.s_addr = inet_addr("224.0.0.5"); // Multicast group address
    multicast_request.imr_interface.s_addr = inet_addr("127.0.0.1");
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast_request, sizeof(multicast_request));
    char buffer[1024];
    while (1) {
        int recv_len = recv(sock, buffer, sizeof(buffer), 0);
        if (recv_len > 0) {
            buffer[recv_len] = '\0';
            printf("Received message: %s\n", buffer);
        }
    }
    close(sock);
    return 0;
}