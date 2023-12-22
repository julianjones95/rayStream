#include <math.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <SDL.h>
#include "variables.h"
#include <iostream>
#include "Player.h"

int playerId;

#define PI 3.14259265

#define PORT 8080


int Player::sendPlayerData(bool inc, bool dec, float * angle, bool direction) {

    int socket_fd;
    struct sockaddr_in serv_addr;
    
    struct MovementData data;

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

    int shouldServerProcessMoveData = 1;

    sendto(socket_fd,
           &shouldServerProcessMoveData,
           sizeof(shouldServerProcessMoveData),
           0,
           (struct sockaddr *) &serv_addr,
           sizeof(serv_addr));



    // Initialize data to send to server
    data.id = playerId; 
    data.x = inc;
    data.y = dec;
    data.direction = direction;

    // Send data to server here
    sendto(
        socket_fd, 
        &data, 
        sizeof(data), 
        0, 
        (struct sockaddr *) &serv_addr, 
        sizeof(serv_addr)
    );

    // Initialize Response variable
    struct MovementData response;
    int server_address_len = sizeof(serv_addr);

    // Receieve response from server
    recvfrom(
        socket_fd, 
        &response, 
        sizeof(response), 
        0, 
        (struct sockaddr *)&serv_addr, 
        (socklen_t*)&server_address_len
    );
    
    // Append response data to player object
    playerId = response.id;
    playerRect.x = response.x;
    playerRect.y = response.y;
    *angle = response.angle;
    close(socket_fd);

    return 0;
}

int Player::getPlayerVector() {

    int socket_fd;
    struct sockaddr_in serv_addr;

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
    
    int shouldServerProcessMoveData = 2;

    sendto(
        socket_fd,
        &shouldServerProcessMoveData,
        sizeof(shouldServerProcessMoveData),
        0,
        (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)
    );

    int testData = 69;

    sendto(socket_fd, &testData, sizeof(testData), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    int server_address_len = sizeof(serv_addr);

    int rowsPlayerVect;
    // Get the number of rows to recv from server
    recvfrom(
        socket_fd,
        &rowsPlayerVect,
        sizeof(rowsPlayerVect),
        0,
        (struct sockaddr *)&serv_addr,
        (socklen_t*)&server_address_len
    );

        for(int i=1; i<rowsPlayerVect; i++){

        struct MovementData pVrow;
    
        // Receieve response from server
        recvfrom(
            socket_fd,
            &pVrow, 1024,
            0,
            (struct sockaddr *)&serv_addr,
            (socklen_t*)&server_address_len
        );
        
        std::cout 
            << "player ID: " 
            << pVrow.id << "X: " 
            << pVrow.x  << "Y: " 
            << pVrow.y  << 
            std::endl; 
 
    }

    close(socket_fd);

    return 0;
}

void Player::movePlayer (bool upArrowDown,
                         bool downArrowDown,
                         bool leftArrowDown,
                         bool rightArrowDown) {
    if (upArrowDown) {
        sendPlayerData(true,false,&angle,false);
    }
    if (downArrowDown) {
        sendPlayerData(false,true,&angle,false);
    }
    if (leftArrowDown) {
        sendPlayerData(false,false,&angle,true);
    }
    if (rightArrowDown) {
        sendPlayerData(false,false,&angle,false);
    }

}
