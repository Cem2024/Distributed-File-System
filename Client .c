#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>



int main() {

    struct sockaddr_in6 client_addr;
    int* buffer = malloc(sizeof(char) * 1024);

    int client_socket = socket(AF_INET6, SOCK_STREAM, 0);

    // Initialise Client Address

    client_addr.sin6_family = AF_INET6;  // IPv6
    client_addr.sin6_addr = in6addr_any; //Possible to connect with every IPv6 IP
    client_addr.sin6_port = htons(8000); // Port 8000, Host-Byte in Netzwerk-Byte

ls

}