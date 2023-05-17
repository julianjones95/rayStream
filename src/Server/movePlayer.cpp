#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "movePlayer.h"
using std::vector;

#define PI 3.14159265

 int map[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,0,0,2,0,0,0,0,0,0,0,0,1,
    1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,
    1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,
    1,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};


int resWidth = 512, resHeight = 512;
int playerWidth = resWidth/64, playerHeight = resHeight/64;
int squareLength =32;
int playerCount = 0; 
int pdx =1, pdy = 1;
float angle;

struct sockaddr_in address;

void Player::movePlayer(int socket_fd, int addrlen) {

    struct Data data;
    int valread = recvfrom(socket_fd, &data, sizeof(data), MSG_WAITALL, (struct sockaddr *) &address, (socklen_t*) &addrlen);


    class Player currentPlayer;
    // Assigns playerID and initializes player object if not assigned 
    if(data.id < 1){
        currentPlayer.id = playerCount++; 
        currentPlayer.positionX = 216;
        currentPlayer.positionY = 216;
        playerVector.push_back(currentPlayer);
    }
    else{
        currentPlayer.id = data.id;
    }

    // Movement Logic    
    if (data.x==1 && data.y==0) {
        playerVector[currentPlayer.id].positionX += pdx;
        playerVector[currentPlayer.id].positionY += pdy;
    }
    if (data.x==0 && data.y==1) {
        playerVector[currentPlayer.id].positionX -= pdx;
        playerVector[currentPlayer.id].positionY -= pdy;
    }
    if (data.x==0 && data.y==0 && data.direction == true) {
        playerVector[currentPlayer.id].angle -= PI/32;
        if(playerVector[currentPlayer.id].angle<0){ playerVector[currentPlayer.id].angle += 2*PI; };
        pdx = cos(playerVector[currentPlayer.id].angle)*5;
        pdy = sin(playerVector[currentPlayer.id].angle)*5;
    }
    if (data.x==0 && data.y==0 && data.direction == false) {
        playerVector[currentPlayer.id].angle += PI/32;
        if(playerVector[currentPlayer.id].angle>2*PI){ playerVector[currentPlayer.id].angle -= 2*PI; };
        pdx = cos(playerVector[currentPlayer.id].angle)*5;
        pdy = sin(playerVector[currentPlayer.id].angle)*5;
    }
    
    int x = playerVector[currentPlayer.id].positionX/32 +1;
    int y = playerVector[currentPlayer.id].positionY/32 +1;

    // Wall Checking
    if(map[y*16 + x-1]==1) {
        //std::cout << x << "," << y << "below" << std::endl;
        if (playerVector[currentPlayer.id].positionY  > y*squareLength -8) {
            playerVector[currentPlayer.id].positionY = y*squareLength -8;
        }
    } 
    if(map[(y-1)*16 + x-1 ]==1) {
        // std::cout << x << "," << y << "above" << std::endl;
        if (playerVector[currentPlayer.id].positionY < y*squareLength ) {
            playerVector[currentPlayer.id].positionY = y*squareLength +1 ;
        }
    }  
    if(map[(y-1)*16 + x]==1) {
        //std::cout << x*squareLength << "," << positionX << "right" << std::endl;
        if (playerVector[currentPlayer.id].positionX > x*squareLength-8 ) {
            playerVector[currentPlayer.id].positionX = x*squareLength-8;
        }

    }

    // To do (easy first bug): 
    // Strange behaviour if you approach a wall on the wall's right
    // side ( approaching from the left ) . I call it the "teleport
    // you will move very quickly downward. This is probably due to
    // you hitting one of the rules above and being moved.
    if(map[(y-1)*16 + x-1]==1) {
        //std::cout << x << "," << y << "left Bound" << std::endl;
        if (playerVector[currentPlayer.id].positionX < x*squareLength-9) {
            playerVector[currentPlayer.id].positionX = x*squareLength-9;
        }

    }
    
    // OOB Bound checking
    if (playerVector[currentPlayer.id].positionX< squareLength){
        playerVector[currentPlayer.id].positionX = squareLength;
    }
    else if (playerVector[currentPlayer.id].positionX + playerWidth + squareLength - 1 >= resWidth) {
        playerVector[currentPlayer.id].positionX = resWidth - playerWidth - squareLength;
    }
    if (playerVector[currentPlayer.id].positionY < squareLength) {
        playerVector[currentPlayer.id].positionY = squareLength;
    }
    else if (playerVector[currentPlayer.id].positionY + playerHeight + squareLength - 1 >= resHeight) {
        playerVector[currentPlayer.id].positionY = resHeight - playerHeight - squareLength;
    }


    // Initialize response variables
    struct Data response;
    response.id = playerVector[currentPlayer.id].id;
    response.x = playerVector[currentPlayer.id].positionX; 
    response.y = playerVector[currentPlayer.id].positionY;
    response.angle = playerVector[currentPlayer.id].angle;

    // Send response back to client
    struct sockaddr_in client_address = *((struct sockaddr_in *)&address);
    int client_address_len = sizeof(client_address);
    sendto(socket_fd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, client_address_len);

}


void Player::sendPlayerVector(int socket_fd, int addrlen) {

        std::cout << "running Server" << std::endl;
        int testData;
        int valread = recvfrom(socket_fd, &testData, sizeof(testData), MSG_WAITALL, (struct sockaddr *) &address, (socklen_t*) &addrlen);

        std::cout << "rcvd data"<< testData << std::endl;

        // Send player vector to client
        struct sockaddr_in client_address = *((struct sockaddr_in *)&address);
        int client_address_len = sizeof(client_address);

        int rowsPlayerVect = playerVector.size();

        sendto(socket_fd, &rowsPlayerVect, sizeof(rowsPlayerVect), 0, (struct sockaddr *)&client_address, client_address_len);


        for(int i=1; i<playerVector.size(); i++){
            std::cout << "sent data, playerVector ids: " << playerVector[i].id << std::endl;
            
            // Initialize the playerVector row to send the data to the client
            struct Data pVrow;
            pVrow.id = i;
            pVrow.x = playerVector[i].positionX;
            pVrow.y = playerVector[i].positionY;
            pVrow.angle = playerVector[i].angle;
            sendto(socket_fd, &pVrow, sizeof(pVrow), 0, (struct sockaddr *)&client_address, client_address_len);
        }

}

