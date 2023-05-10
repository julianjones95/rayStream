#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <math.h>
#define PI 3.14159265

struct Data {
    float x;
    float y;
    float angle;
    float direction;
};

float positionX = 0;
float positionY = 0;
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

        // Send response to client

        struct Data response;
        response.x = positionX; 
        response.y = positionY;
        response.angle = angle;

        struct sockaddr_in client_address = *((struct sockaddr_in *)&address);
        int client_address_len = sizeof(client_address);
        sendto(socket_fd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, client_address_len);

    }
}
