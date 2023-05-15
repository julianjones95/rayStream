// Server side C program to demonstrate Socket programming using SOCK_DGRAM
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "movePlayer.h"

#define PI 3.14159265
#define PORT 8080

int main(int argc, char const *argv[]) {

    struct sockaddr_in address;

    int socket_fd;
    int addrlen = sizeof(address);
    
    // Creating socket file descriptor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    // If bind fails throw error 
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    Player currentPlayer;
    currentPlayer.movePlayer(socket_fd, addrlen);

    return 0;
}

