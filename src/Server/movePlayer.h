#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>

extern float positionX;
extern float positionY;
extern int pdx, pdy;
extern float angle;

void movePlayer(int ,int);
