#include "drawOtherPlayers.h"
#include "variables.h"

void drawOtherPlayers(SDL_Renderer *renderer) {

    for(int i=0; i<2; i++) {
        SDL_Rect otherPlayer;
        otherPlayer.w = 512/64;
        otherPlayer.h = 512/64;
        otherPlayer.x = 20*i + resW/4 - otherPlayer.w/2;  
        otherPlayer.y = 20*i + resH/2 - otherPlayer.h/2;  
        SDL_SetRenderDrawColor(renderer, 255, 155, 20, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &otherPlayer);
    }
}


