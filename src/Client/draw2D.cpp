#include "draw2D.h"
#include "variables.h"

void draw2D::Map(SDL_Renderer *renderer) {
    int x0,y0;
    for(int x =0; x< mapX; x++) {
        for(int y=0; y< mapY; y++) { 

            SDL_Rect wall;
            wall.x = x*(resW/mapX/2)+1; //1440
            wall.y = y*(resH/mapY)+1;
            wall.w = (resW/mapX/2)-1; //1440
            wall.h = (resH/mapY)-1;

            if(map[y*mapX + x]==1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &wall);
            } else {
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &wall);
            }
        }
    }
}


void draw2D::otherPlayers(SDL_Renderer *renderer) {

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


