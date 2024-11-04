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

    // Initialise client address

    client_addr.sin6_family = AF_INET6;  // IPv6
    client_addr.sin6_addr = in6addr_any; //Possible to connect with every IPv6 IP
    client_addr.sin6_port = htons(8000); // Port 8000, Host-Byte in Netzwerk-Byte

    //::1 localhost for IPv6
    //inet_pton converts IPv6 address to binary for struct sockaddr_in6
    if(inet_pton(AF_INET6, "::1", &client_addr.sin6_addr) <= 0) {
        perror("Address not valid");
        close(client_socket);
        exit(1);
    }


    if(connect(client_socket, (const struct sockaddr *)&client_addr, sizeof(struct sockaddr_in6)) < 0){
        perror("Could not connect");
        close(client_socket);
        exit(1);
    }


    ssize_t send_message = send(client_socket, buffer, 500, 0);
    if (send_message == -1) {
        perror("Could not send message");
        close(client_socket);
        exit(1);
    }


    ssize_t receive_message = recv(client_socket, buffer, 1024, 0);
    if (receive_message == -1) {
        perror("Receive failed");
        close(client_socket);
        exit(1);
    }


    close(client_socket);
    free(buffer);

}