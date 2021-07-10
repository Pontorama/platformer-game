#ifndef GameObject_h
#define GameObject_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2.h"
#include "Constants.h"
#include "TextureManager.h"
#include <iostream>
#include <list>
#include "Hitbox.h"

// TODO implement hit detection
// Use _destRect for bounding box?

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
        Vector2 _pos;
        int _mask;
        SDL_Texture* _objTexture;
        SDL_Rect _srcRect, _destRect;
        SDL_Renderer* _ren;

        std::list<Hitbox> hitboxes;
};

#endif /* GameObject_h */