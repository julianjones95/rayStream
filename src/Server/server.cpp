// Server side C program to demonstrate Socket programming using SOCK_DGRAM
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

struct Data {
    float x;
    float y;
    float z;
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

    while(1) {
        
        struct Data data;
        int valread = recvfrom(socket_fd, &data, sizeof(data), MSG_WAITALL, (struct sockaddr *) &address, (socklen_t*) &addrlen);
        printf("Received Data:\n x = %f\n y = %f\n z = %f\n", data.x, data.y, data.z);

        //float response = buffer +1;

        // Writes the message
        //sendto(socket_fd, &response , sizeof(response), 0, (struct sockaddr *) &address, addrlen);
    }
    return 0;
}

