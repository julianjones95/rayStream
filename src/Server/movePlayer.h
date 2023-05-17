#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#include <vector>
using std::vector;


extern float positionX;
extern float positionY;
extern int pdx, pdy;
extern float angle;

struct Data {
    int id;
    float x;
    float y;
    float angle;
    float direction;
};

class Player {
    public:
    int id;
    float positionX;
    float positionY;
    float angle;

    vector<Player> playerVector;

    void movePlayer(int socket_fd, int addrlen);

    void sendPlayerVector(int socket_fd, int addrlen);


};




