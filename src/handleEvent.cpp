#include <SDL.h>
#include "handleEvent.h"

void handleEvent(bool *appIsRunning, bool *upArrowDown, bool *downArrowDown, bool *leftArrowDown, bool *rightArrowDown) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Handle each specific event
        if (event.type == SDL_QUIT) {
            *appIsRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                *upArrowDown = true;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                *leftArrowDown = true;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                *downArrowDown = true;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                *rightArrowDown = true;
            }
        }
        else if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                *upArrowDown = false;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                *leftArrowDown = false;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                *downArrowDown = false;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                *rightArrowDown = false;
            }
        }
    }
}

