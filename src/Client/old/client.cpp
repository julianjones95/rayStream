// Client side C program to demonstrate Socket programming using SOCK_DGRAM
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

struct Data {
    float x;
    float y;
    float z;
};

#define PORT 8080

int main(int argc, char const *argv[]) {
    int socket_fd;
    struct sockaddr_in serv_addr;
    
    struct Data data;

    for(int i = 0; i<10000000; i++){

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

        data.x = i;
        data.y = 100 + i;
        data.z = 1000 + i;


        sendto(socket_fd, &data, sizeof(data), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
        close(socket_fd);

        }
    return 0;
}
