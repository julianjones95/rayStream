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

    int decision = 1;
    // Send ddecision data to server here
    // This tells the server to process move data
    sendto(socket_fd, &decision, sizeof(decision), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));



    // Initialize data to send to server
    data.id = playerId; 
    data.x = inc;
    data.y = dec;
    data.direction = direction;

    // Send data to server here
    sendto(socket_fd, &data, sizeof(data), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // Initialize Response variable
    struct Data response;
    int server_address_len = sizeof(serv_addr);

    // Receieve response from server
    int valread = recvfrom(socket_fd, &response, 1024, 0, (struct sockaddr *)&serv_addr, (socklen_t*)&server_address_len);
    //printf("Rec resp:\n x = %f\n y = %f\n", response.x, response.y);
    
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
    
    int decision = 0;
    // Send ddecision data to server here
    // This tells the server to process move data
    sendto(socket_fd, &decision, sizeof(decision), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    int testData = 12;

    sendto(socket_fd, &testData, sizeof(testData), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    int server_address_len = sizeof(serv_addr);


    int rowsPlayerVect;
    // Get the number of rows to recv from server
    int valread = recvfrom(socket_fd, &rowsPlayerVect, 1024, 0, (struct sockaddr *)&serv_addr, (socklen_t*)&server_address_len);
 
  
    for(int i=1; i<rowsPlayerVect; i++){
        std::cout << "num of rows" << rowsPlayerVect << std::endl;

        struct Data pVrow;
    
        // Receieve response from server
        int valread = recvfrom(socket_fd, &pVrow, 1024, 0, (struct sockaddr *)&serv_addr, (socklen_t*)&server_address_len);
        
        // playerVector.push_back(pVrow); 

        // Note for next commit:
        // This implementation works as intended.
        // We get the info from the server iteratively
        // then print it to the screen. However this does 
        // not dynamically save to our playerVector. 
        // We also have a bug where 2 players cannot join
        // simultaneously. I believe it is to do with our 
        // 2 server methods clashing and causing a segfault.
        std::cout << "player ID: " << pVrow.id << "X: " << pVrow.x << "Y: " << pVrow.y << std::endl; 
 
    }
//    for(int i=0; i<playerVector.size(); i++)
//        std::cout << " rcvd other, players ids: " << playerVector[i].id << std::endl;

    close(socket_fd);

    return 0;
}



void Player::movePlayer (bool upArrowDown, bool downArrowDown, bool leftArrowDown, bool rightArrowDown) {
    // Movement Logic    
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
