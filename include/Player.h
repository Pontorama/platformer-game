#ifndef Player_h
#define Player_h

#include "SDL2/SDL_image.h"
#include "Constants.h"
#include "Hitbox.h"
#include <iostream>
#include <cmath>
#include "DebugLogger.h"
#include "Creature.h"

class Player : public Creature {
    public:
        Player();
        Player(GameObject* base, int id);
        Player(SDL_Renderer* ren);
        Player(SDL_Renderer* ren, Vector2 pos);
        ~Player();

        Vector2 getSpeed();
        
        void handleEvents(SDL_Event e);
        void handleInput(const uint8_t* state);
        void update();
        void move();
    private:
        float _jumpSpeed;
        bool _doJump;

        void setPosition(Vector2 newPos);
        const float MAX_DIR_LEN = 1.5;
        const float PLAYER_MAX_SPEED = 0.5;
        const float PLAYER_SLOWDOWN_ACC = 0.1;
        const float PLAYER_MIN_SPEED = PLAYER_MAX_SPEED / 8;
        void terrainCollision(Hitbox* local, Hitbox* terrain);
        void init();
};

#endif /* Player_h */
