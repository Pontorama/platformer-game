#ifndef GameObject_h
#define GameObject_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2.h"
#include "Constants.h"
#include "TextureManager.h"
#include <iostream>

class GameObject{
    public:
        GameObject();
        GameObject(const char* textureSheet, SDL_Renderer* ren);
        ~GameObject();  

        float getXPos();
        float getYPos();
        Vector2 getPos();

        void update();
        void render();
    protected:
        Vector2 pos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* ren;
};

#endif /* GameObject_h */