#include "drawMap.h"
#include "variables.h"

void drawMap2D(SDL_Renderer *renderer) {
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


