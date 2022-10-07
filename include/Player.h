#ifndef Player_h
#define Player_h

#include "SDL2/SDL_image.h"
#include "Constants.h"
#include "Hitbox.h"
#include <iostream>
#include <cmath>
#include "DebugLogger.h"
#include "Creature.h"
#include "ServiceLocator.h"

class Player : public Creature {
    public:
        Player();
        Player(SDL_Renderer* renderer, Animator* animator, vector<Hitbox*> hitboxes, Vector2 pos, string name);
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
        float MAX_DIR_LEN = 1.5;
        float PLAYER_MAX_SPEED_X;
        float PLAYER_MAX_SPEED_Y;
        float PLAYER_SLOWDOWN_ACC = 0.1;
        float PLAYER_MIN_SPEED_X;
        void terrainCollision(Hitbox* local, Hitbox* terrain);
        void init();
};

#endif /* Player_h */
