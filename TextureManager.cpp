#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName, SDL_Renderer* ren){
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);

    return texture;
}
