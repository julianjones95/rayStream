#include "movePlayer.h"
#include <SDL.h>
#include <math.h>
#define PI 3.14259265

void movePlayer (SDL_Rect *playerRect, int resW, int resH, bool upArrowDown, bool downArrowDown, bool leftArrowDown, bool rightArrowDown) {

    // Movement Logic    
    if (upArrowDown) {
        sendPlayerData(playerRect,true,false,&angle,false);
    }
    if (downArrowDown) {
        sendPlayerData(playerRect,false,true,&angle,false);
    }
    if (leftArrowDown) {
        sendPlayerData(playerRect,false,false,&angle,true);
    }
    if (rightArrowDown) {
        sendPlayerData(playerRect,false,false,&angle,false);
    }

    // Bound checking
    if (playerRect->x < 0) {
        playerRect->x = 0;
    }
    else if (playerRect->x + playerRect->w - 1 >= resW) {
        playerRect->x = resW - playerRect->w;
    }
    if (playerRect->y < 0) {
        playerRect->y = 0;
    }
    else if (playerRect->y + playerRect->h - 1 >= resH) {
        playerRect->y = resH - playerRect->h;
    }

}



