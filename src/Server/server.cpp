// Server side C program to demonstrate Socket programming using SOCK_DGRAM
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265

struct Data {
    float x;
    float y;
    float angle;
    float direction;
};

#define PORT 8080

int main(int argc, char const *argv[]) {

    int socket_fd;
    struct sockaddr_in address;

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

    float positionX = 0;
    float positionY = 0;
    int pdx =1, pdy =1;
    float angle;

    while(1) {
        
        struct Data data;
        int valread = recvfrom(socket_fd, &data, sizeof(data), MSG_WAITALL, (struct sockaddr *) &address, (socklen_t*) &addrlen);
        // Print server data receieved
        //printf("Received Data:\n x = %f\n y = %f\n z = %f\n", data.x, data.y, data.direction);

       
        // Movement Logic    
        if (data.x==1 && data.y==0) {
            positionX += pdx;
            positionY += pdy;
        }
        if (data.x==0 && data.y==1) {
            positionX -= pdx;
            positionY -= pdy;
        }
        if (data.x==0 && data.y==0 && data.direction == true) {
            angle -= PI/32;
            if(angle<0){ angle += 2*PI; };
            pdx = cos(angle)*5;
            pdy = sin(angle)*5;
        }
        if (data.x==0 && data.y==0 && data.direction == false) {
            angle += PI/32;
            if(angle>2*PI){ angle -= 2*PI; };
            pdx = cos(angle)*5;
            pdy = sin(angle)*5;
        }


        // Send response to client
    
        struct Data response;
        response.x = positionX; 
        response.y = positionY;
        response.angle = angle;

        struct sockaddr_in client_address = *((struct sockaddr_in *)&address);
        int client_address_len = sizeof(client_address);
        sendto(socket_fd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, client_address_len);

    }

    return 0;
}

