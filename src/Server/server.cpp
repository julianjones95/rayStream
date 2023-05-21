// Server side C program to demonstrate Socket programming using SOCK_DGRAM
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include "Player.h"

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

    // Get data to choose which server action to run
    int decision;

    while(1) {

        int valread = recvfrom(socket_fd, &decision, sizeof(decision), MSG_WAITALL, (struct sockaddr *) &address, (socklen_t*) &addrlen);
        
        if(decision ==1){
            currentPlayer.movePlayer(socket_fd, addrlen);
            
        }
        else if(decision == 2){
            currentPlayer.sendPlayerVector(socket_fd,addrlen);
        }
    }
    return 0;
}

