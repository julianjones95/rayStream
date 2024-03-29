#pragma once
#include <SDL.h>
#include <vector>

using std::vector;

struct MovementData {
    int id;
    float x;
    float y;
    float angle;
    float direction;
};


class Player {
    public:
    SDL_Rect playerRect;

    vector<MovementData> playerVector;

    int sendPlayerData(bool inc, bool dec, float* angle, bool direction);

    void movePlayer(bool upArrowDown, bool downArrowDown, bool leftArrowDown, bool rightArrowDown);

    int getPlayerVector();


};

