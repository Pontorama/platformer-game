#ifndef Player_h
#define Player_h

#include "GameObject.h"
#include "SDL2/SDL_image.h"
#include "Constants.h"
#include "Hitbox.h"
#include <iostream>
#include <cmath>

class Player : public GameObject{
    public:
        Player();
        Player(const char* textureSheet, SDL_Renderer* ren);
        ~Player();

        Vector2 getSpeed();
        void handleEvents(SDL_Event e);
        void actOnCollision(GameObject* other);
        void update();
        void render();
    private:
        Vector2 _speed;
        float _acceleration;
        Vector2 _dir; // The direction the player is moving in, should be normalized
        const float MAX_DIR_LEN = 1.5;
        const float PLAYER_MAX_SPEED = 0.5;
        const float PLAYER_SLOWDOWN_ACC = 0.1;
        const float PLAYER_MIN_SPEED = PLAYER_MAX_SPEED / 8;
};

#endif /* Player_h */