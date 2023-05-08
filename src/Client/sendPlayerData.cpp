// Client side C program to demonstrate Socket programming using SOCK_DGRAM
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <SDL.h>
#include "variables.h"


struct Data {
    float x;
    float y;
    float angle;
    float direction;
};

#define PORT 8080

int sendPlayerData(SDL_Rect *playerRect, bool inc, bool dec, float * angle, bool direction) {
    int socket_fd;
    struct sockaddr_in serv_addr;
    
    struct Data data;

    // Creating socket file descriptor
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    data.x = inc;
    data.y = dec;
    data.direction = direction;
    // Send data to server here
    sendto(socket_fd, &data, sizeof(data), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));


    struct Data response;

    int server_address_len = sizeof(serv_addr);
    

    // Receieve response from server
    int valread = recvfrom(socket_fd, &response, 1024, 0, (struct sockaddr *)&serv_addr, (socklen_t*)&server_address_len);
    //printf("Rec resp:\n x = %f\n y = %f\n", response.x, response.y);

    playerRect->x = response.x;
    playerRect->y = response.y;
    *angle = response.angle;
    close(socket_fd);

    return 0;
}
