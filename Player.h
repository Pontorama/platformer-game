#ifndef Player_h
#define Player_h

#include "GameObject.h"
#include "SDL2/SDL_image.h"
#include "Constants.h"
#include <iostream>

class Player : GameObject{
    public:
        Player();
        Player(const char* textureSheet, SDL_Renderer* ren);
        ~Player();

        float getSpeed();
        void handleEvents(SDL_Event e);
        void update();
        void render();
    private:
        float speed;
        Vector2 dir; // The direction the player is moving in, should be normalized
};

#endif /* Player_h */