// Created by Ali Behfarnia on 11/24.

// socket programming (Def)
// Socket programming in Inter-Process Communication (IPC) allows processes to communicate with each other over
// a network or within the same system. 

//Key API Functions:
// a. socket(): Creates a socket.
// b. connect(): Initiates connection (client-side).
// c. listen() / accept(): Wait for client connections (server-side).
// d. bind(): Assigns IP/port to a socket.
// e. send()/recv(): Data exchange.

// Socket Types: 1) Stream or TCP, 2) Datagram or UDP.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int aa, char* hh[]) {

    // ============ socket =============
    // Purpose: Creates a socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET: Specifies the address family for IPv4.
    // SOCK_STREAM: Specifies the type of socket, here it's a TCP socket.
    // 0: Specifies the protocol, where 0 lets the system choose the default protocol for SOCK_STREAM, which is TCP.

    char* ip = "108.177.122.147"; // Example: google.com

    // =========== socket address structure =============
    // Purpose: Sets up the socket address structure address to connect to the server.
    struct sockaddr_in address;
    address.sin_family = AF_INET; 
    //Sets the address family to IPv4.

    address.sin_port = htons(80);
    // Sets the port number to 80 (HTTP), 
    // using htons to ensure the port is in network byte order.

    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    // This converts the ip string to a binary format and stores it in address.sin_addr.s_addr.
    // Note: s_addr is the actual field within sin_addr that holds the IPv4 address in network byte order.

    // Purpose: Attempts to connect the socket to the specified IP address and port.
    int result = connect(socket_fd, (const struct sockaddr *) &address, sizeof(address));
    // Possible outcomes: 0 or -1
    // A return value of 0 means the connection was successfully, and -1 NOT successful

    if (result == 0){
        printf("Connection is successful!");
    }
    printf("\n");
    return 0;

}