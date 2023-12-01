#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() 
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in multicast_addr;
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr("224.0.0.5"); // Multicast group address
    multicast_addr.sin_port = htons(5000); // Multicast port
    int loop = 1; // Set the IP_MULTICAST_LOOP socket option
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    struct in_addr local_interface;
    local_interface.s_addr = inet_addr("127.0.0.1");
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &local_interface, sizeof(local_interface));
    const char* message = "This is a multicast message";
    sendto(sock, message, strlen(message), 0, (struct sockaddr*)&multicast_addr, sizeof(multicast_addr));
    close(sock);
    return 0;
}