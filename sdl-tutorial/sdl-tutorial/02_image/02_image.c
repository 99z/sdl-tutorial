//
//  02_image.c
//  SDL_tutorial
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
SDL_Surface* gHelloWorld = NULL;

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
    gHelloWorld = SDL_LoadBMP("02_image/hello_world.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    
    return success;
}

void closeSDL() {
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    
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
            // Load image to surface
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            // Update the front buffer so we can see the image
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(2000);
        }
    }
    
    closeSDL();
    return 0;
}
