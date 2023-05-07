#include <math.h>
#include <iostream>
#include <SDL.h>
#include "handleEvent.h"
#include "movePlayer.h"
#include "variables.h"
#include "drawRays3D.h"
#include "drawMap.h"
#define PI 3.14259265
#define Rad PI/1440 //This is actually an eigth radian




int main(int argc, char const *argv[]) {

    SDL_Rect playerRect;
    playerRect.w = 512/64;
    playerRect.h = 512/64;
    playerRect.x = resW/4 - playerRect.w/2;  
    playerRect.y = resH/2 - playerRect.h/2;  
    
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "3D RayCast",        // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        resW,                     // width, in pixels
        resH,                     // height, in pixels
        SDL_WINDOW_SHOWN         // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        // In the case that the renderer could not be made...
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Runs the main game frames
    while (appIsRunning) {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Handle new events
        handleEvent( &appIsRunning, &upArrowDown, &downArrowDown, &leftArrowDown, &rightArrowDown);

        // Handle movement of character
        movePlayer(&playerRect, resW, resH, upArrowDown, downArrowDown, leftArrowDown, rightArrowDown);
        
        // Function to draw the 2d Map
        drawMap2D(renderer);

        // Draw the 3D raycast
        drawRays3D(&playerRect, renderer);       

        SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &playerRect);
        SDL_RenderDrawLine(renderer, playerRect.x, playerRect.y, playerRect.x + 10*pdx, playerRect.y+10*pdy);
        SDL_RenderPresent(renderer);
        
    }


    // Code to exit and cleanup the program
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    std::cout << "exiting..." << std::endl;
    SDL_Quit();
    return 0;
}
