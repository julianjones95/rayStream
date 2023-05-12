#pragma once
#include <SDL.h>

class Player {
public:
    SDL_Rect playerRect;

    struct Data {
        float x;
        float y;
        float angle;
        float direction;
    };

    int sendPlayerData(bool inc, bool dec, float* angle, bool direction);

    void movePlayer(int resW, int resH, bool upArrowDown, bool downArrowDown, bool leftArrowDown, bool rightArrowDown);
};

