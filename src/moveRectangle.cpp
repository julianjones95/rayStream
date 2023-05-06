#include "moveRectangle.h"
#include <SDL.h>
#include <math.h>
#define PI 3.14259265

void moveRectangle (SDL_Rect *playerRect, int resW, int resH, bool upArrowDown, bool downArrowDown, bool leftArrowDown, bool rightArrowDown) {

    // Movement Logic    
    if (upArrowDown) {
        playerRect->x += pdx;
        playerRect->y += pdy;
    }
    if (downArrowDown) {
        playerRect->x -= pdx;
        playerRect->y -= pdy;
    }
    if (leftArrowDown) {
        angle -= PI/32;
        if(angle<0){ angle += 2*PI; };
        pdx = cos(angle)*5;
        pdy = sin(angle)*5;
    }
    if (rightArrowDown) {
        angle += PI/32;
        if(angle>2*PI){ angle -= 2*PI; };
        pdx = cos(angle)*5;
        pdy = sin(angle)*5;
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



