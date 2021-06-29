#ifndef Player_h
#define Player_h

#include "GameObject.h"
#include "SDL2/SDL_image.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

class Player : GameObject{
    public:
        Player();
        Player(const char* textureSheet, SDL_Renderer* ren);
        ~Player();

        Vector2 getSpeed();
        void handleEvents(SDL_Event e);
        void update();
        void render();
    private:
        Vector2 speed;
        float acceleration;
        Vector2 dir; // The direction the player is moving in, should be normalized
        const float MAX_DIR_LEN = 1.5; // Does not need to be global
        const float PLAYER_MAX_SPEED = 0.2;
};

#endif /* Player_h */