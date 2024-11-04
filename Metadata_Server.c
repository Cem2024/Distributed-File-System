#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    struct sockaddr_in6 server_addr, client_addr;
    char* buffer = malloc(sizeof(char) * 1024);

    //Creating IPv6 socket
    int mainSocket = socket(AF_INET6, SOCK_STREAM, 0);
    if (mainSocket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    //Initialise address structure
    server_addr.sin6_family = AF_INET6;  // IPv6
    server_addr.sin6_addr = in6addr_any; //Possible to connect with every IPv6 IP
    server_addr.sin6_port = htons(8000); // Port 8000, Host-Byte in Netzwerk-Byte

    //Bind Socket at Address and port
    if (bind(mainSocket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        close(mainSocket);
        exit(1);
    }

    //Waiting for possible connections (Queue max. 3)
    int list = listen(mainSocket, 3);
    if(list == -1){
        perror("listen failed");
        close(mainSocket);
        exit(1);
    }

    //Accepting client and creating new socket
    socklen_t client_addr_length = sizeof(client_addr);
    int client_socket = accept(mainSocket, (struct sockaddr*) &client_addr, &client_addr_length);
    if (client_socket == -1) {
        perror("Connection to Client failed");
        close(mainSocket);
        exit(1);
    }

    //inet_ntop changes the client address to readable version
    char client_ip[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip, sizeof(client_ip));
    printf("Address of Client: %s, Port: %d\n", client_ip, ntohs(client_addr.sin6_port));



    //Receive message
    ssize_t receive_message = recv(client_socket, buffer, 1024, 0);
    if (receive_message == -1) {
        perror("Receive failed");
        close(client_socket);
        exit(1);
    }

    //Send message
    ssize_t send_message = send(client_socket, buffer, 500, 0);
    if (send_message == -1) {
        perror("Could not send message");
        close(client_socket);
        exit(1);
    }


    //free ressource
    close(mainSocket);
    close(client_socket);
    free(buffer);

    return 0;
}