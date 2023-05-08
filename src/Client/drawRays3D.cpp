#include "variables.h"
#include <SDL.h>
#include <math.h>

#define PI 3.14259265
#define Rad PI/1440 //This is actually an eigth radian



float rayDist(float ax, float ay, float bx, float by, float ang) {
    return ( sqrt(pow(bx-ax,2) + pow(by-ay,2)) );
}


void drawRays3D(SDL_Rect *playerRect, SDL_Renderer *renderer){

    int mx, my, mp, dof, bitshift =5;
    float rayX, rayY, rayAngle = angle, xo, yo, finalDist;     
    rayAngle = angle - (Rad)*256;
    if(rayAngle < 0) rayAngle += 2*PI;
    if(rayAngle > 2*PI) rayAngle -= 2*PI;
    
    for (int r=0; r<512; r++){ 
        // Check Horizontal lines for ray collisions
        dof=0;
        float distH = 10000000, hx=playerRect->x, hy=playerRect->y;
        float aTan = -1/tan(rayAngle);
        // Character is Looking up
        if(rayAngle > PI) {
            // This takes the pointer and bit shifts it 6 places right
            // then "bitshift" places left giving an interval of 2^bitshift
            // This effectively increments rayY by 2^bitshift each vertical box
            rayY = (((int)(playerRect->y)>>bitshift)<<bitshift) - 0.0001; 
            rayX = ((playerRect->y) - rayY) * aTan + (playerRect->x);
            yo = -pow(2,bitshift);
            xo = -yo*aTan;
        }
        // Character is Looking Down
        if(rayAngle < PI) {
            rayY = (((int)(playerRect->y)>>bitshift)<<bitshift) + pow(2,bitshift); 
            rayX = ((playerRect->y) - rayY) * aTan + (playerRect->x);
            yo = pow(2,bitshift);
            xo = -yo*aTan;
        }
        if(rayAngle==0 || rayAngle == PI) {
            rayX = playerRect->x; 
            rayY = playerRect->y; 
            dof = 8;
        }

        // Cast rays at a length of 'dof' 
        while(dof<16){
            mx=(int)(rayX)>>bitshift; 
            my=(int)(rayY)>>bitshift; 
            mp=my*mapX+mx;
            if(0<mp && mp<mapX*mapY && map[mp]==1) { //Hit a wall
                hx = rayX;
                hy = rayY;
                distH = rayDist(playerRect->x,playerRect->y,hx,hy, rayAngle);
                dof=16; 
            }
            else{ 
                rayX += xo;
                rayY += yo;
                dof +=1;
            }
        } 
    
        // Check Vertical lines
        dof=0;
        float distV = 10000000, vx=playerRect->x, vy=playerRect->y;
        float Tan = -1 * tan(rayAngle);
        // Character is Looking left
        if(rayAngle > PI/2 && rayAngle < 3*PI /2) {
            rayX = (((int)(playerRect->x)>>bitshift)<<bitshift) - 0.0001; 
            rayY = ((playerRect->x) - rayX) * Tan + (playerRect->y);
            xo = -pow(2,bitshift);
            yo = -xo*Tan;
        }
        // Character is Looking right
        if(rayAngle < PI/2 || rayAngle > 3*PI/2 ) {
            rayX = (((int)(playerRect->x)>>bitshift)<<bitshift) + pow(2,bitshift); 
            rayY = ((playerRect->x) - rayX) * Tan + (playerRect->y);
            xo = pow(2,bitshift);
            yo = -xo*Tan;
        }
        if(rayAngle==0 || rayAngle == PI) {
            rayX = playerRect->x; 
            rayY = playerRect->y; 
            dof = 8;
        }

        while(dof<16){
            mx=(int)(rayX)>>bitshift; 
            my=(int)(rayY)>>bitshift; 
            mp=my*mapX+mx;
          //  std::cout << mp <<std::endl;
            if( mp>0 && mp<mapX*mapY && map[mp]==1) { //Hit a wall
                vx = rayX;
                vy = rayY;
                distV = rayDist(playerRect->x,playerRect->y,vx,vy, rayAngle);
                dof=16; 
            }
            else{ 
                rayX += xo;
                rayY += yo;
                dof +=1;
            }
        }

    if(distV>distH) { 
        rayX = hx;
        rayY = hy;   
        finalDist = distH;
        SDL_SetRenderDrawColor(renderer, 80, 105, 180, SDL_ALPHA_OPAQUE);

    } 
    else {
        rayX = vx;
        rayY = vy;
        finalDist = distV;
        SDL_SetRenderDrawColor(renderer, 0, 105, 180, SDL_ALPHA_OPAQUE);

    }
    SDL_RenderDrawLine(renderer, playerRect->x, playerRect->y, rayX, rayY);
   
    // Draw the 3D Walls
    
    float diffAngle = rayAngle - angle;
    if(diffAngle<0) {
        diffAngle += 2*PI;
    }
    if(diffAngle> 2*PI) {
        diffAngle -= 2*PI;
    }
    finalDist = finalDist * cos(diffAngle);
    float lineHeight = (32*512)/finalDist;
    float lineOffset = 256 - lineHeight/2;
    SDL_RenderDrawLine(renderer, r*1 + 513, lineOffset, r*1 + 513, lineHeight+lineOffset);

    if(lineHeight>512) {
        lineHeight = 512;
    }

    // Increment the loop by 1 degree and end loop
    rayAngle += Rad;
    if(rayAngle < 0) rayAngle += 2*PI;
    if(rayAngle > 2*PI) rayAngle -= 2*PI;

    }

}



