#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
//Bilden som skall laddas till skärmen
SDL_Surface* gHelloWorld = NULL;

SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;

bool init(){
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) <0){
        printf("SDL could not initialize, error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        //Create window
        gWindow = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            printf("Window could not be created, error: %s\n", SDL_GetError());
            success = false;
        }
        else{
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL){
                printf("Renderer cannot be created, error: %s\n", SDL_GetError());
                success = false;
            }
            else{
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);

                SDL_Rect testrect;
                testrect.x = 4;
                testrect.y = 4;
                testrect.w = 30;
                testrect.h = 30;

                SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 50);
                SDL_RenderFillRect(gRenderer, &testrect);

                //Initialize draw color
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)) & imgFlags){
                    printf("SDL_image could not be initialized. Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
        }
    return success;
}


SDL_Surface* loadSurface(std::string imagepath){

    // FInal optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image from file
    SDL_Surface* loadedSurface = SDL_LoadBMP(imagepath.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image. Error: %s\n", SDL_GetError());
    }
    else{
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0 );
        if(optimizedSurface == NULL){
            printf("Unable to optimize image %s, error: %s\n", imagepath.c_str(), SDL_GetError());
        }

        //Remove old surface
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

SDL_Texture* loadTexture(std::string texpath){
    //Final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(texpath.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image %s! Error: %s\n", texpath.c_str(), SDL_GetError());
    }
    else{
        //Create a texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL){
            printf("Unable to create texture from %s. Error: %s\n", texpath.c_str(), SDL_GetError());
        }

        //Get rid of loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadMedia(){
    bool success = true;
    
    gTexture = loadTexture("/home/pongu/Code/platformer-game/images/cat.png");
    if(gTexture == NULL){
        printf("Failed to load texture image.\n");
        success = false;
    }

    return success;
}

void close(){
    // Free loaded texture
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}