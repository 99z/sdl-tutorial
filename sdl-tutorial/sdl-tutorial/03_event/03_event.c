//
//  03_event.c
//  sdl-tutorial
//
//  Created by Nicolas Montanaro on 12/23/16.
//  Copyright © 2016 Nicolas Montanaro. All rights reserved.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

// Starts up SDL and creates window
bool init();

// Loads our media
bool loadMedia();

// Frees media, shuts down SDL
void closeSDL();

// Create window to render to
SDL_Window* gWindow = NULL;

// Surface on the window
SDL_Surface* gScreenSurface = NULL;

// Image being loaded to the screen
SDL_Surface* gXout = NULL;

// Window size definitions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init() {
    // Initialization flag
    bool success = true;
    
    // Required initializiation of SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    
    return success;
}

bool loadMedia() {
    // Setting success flag
    bool success = true;
    
    // Load our image
    gXout = SDL_LoadBMP("03_event/x.bmp");
    if (gXout == NULL) {
        printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    
    return success;
}

void closeSDL() {
    // Deallocate surface
    SDL_FreeSurface(gXout);
    gXout = NULL;
    
    // Destroy window
    // Also handles destroying the screen surface
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[]) {
    // Start SDL and create window
    if (!init()) {
        printf("Failed to initialize\n");
    } else {
        // Load media
        if (!loadMedia()) {
            printf("Failed to load media\n");
        } else {
            // Main loop flag
            bool quit = false;
            // Event handler
            SDL_Event e;
            
            // While application is running
            while (!quit) {
                // Handle events
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                
                SDL_BlitSurface(gXout, NULL, gScreenSurface, NULL);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    
    closeSDL();
    return 0;
}
