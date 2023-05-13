#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265

struct Data {
    float x;
    float y;
    float angle;
    float direction;
};

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


float positionX = 216, positionY = 216;
int resWidth = 512, resHeight = 512;
int playerWidth = resWidth/64, playerHeight = resHeight/64;
int squareLength =32;

int pdx =1, pdy =1;
float angle;

struct sockaddr_in address;

void movePlayer(int socket_fd, int addrlen) {

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
        
        int x = positionX/32 +1;
        int y = positionY/32 +1;

        // Wall Checking
        if(map[y*16 + x-1]==1) {
            //std::cout << x << "," << y << "below" << std::endl;
            if (positionY  > y*squareLength -8) {
                positionY = y*squareLength -8;
            }
        } 
        if(map[(y-1)*16 + x-1 ]==1) {
            // std::cout << x << "," << y << "above" << std::endl;
            if (positionY < y*squareLength ) {
                positionY = y*squareLength +1 ;
            }
        }  
        if(map[(y-1)*16 + x]==1) {
            //std::cout << x*squareLength << "," << positionX << "right" << std::endl;
            if (positionX > x*squareLength-8 ) {
                positionX = x*squareLength-8;
            }

        }

        // To do (easy first bug): 
        // Strange behaviour if you approach a wall on the wall's right
        // side ( approaching from the left ) . I call it the "teleport
        // you will move very quickly downward. This is probably due to
        // you hitting one of the rules above and being moved.
        if(map[(y-1)*16 + x-1]==1) {
            //std::cout << x << "," << y << "left Bound" << std::endl;
            if (positionX < x*squareLength-9) {
                positionX = x*squareLength-9;
            }

        }
        
        // OOB Bound checking
        if (positionX< squareLength){
            positionX = squareLength;
        }
        else if (positionX + playerWidth + squareLength - 1 >= resWidth) {
            positionX = resWidth - playerWidth - squareLength;
        }
        if (positionY < squareLength) {
            positionY = squareLength;
        }
        else if (positionY + playerHeight + squareLength - 1 >= resHeight) {
            positionY = resHeight - playerHeight - squareLength;
        }


        // Initialize response variables
        struct Data response;
        response.x = positionX; 
        response.y = positionY;
        response.angle = angle;

        // Send response back to client
        struct sockaddr_in client_address = *((struct sockaddr_in *)&address);
        int client_address_len = sizeof(client_address);
        sendto(socket_fd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, client_address_len);

    }
}
