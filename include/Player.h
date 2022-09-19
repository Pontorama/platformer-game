#ifndef Player_h
#define Player_h

#include "GameObject.h"
#include "SDL2/SDL_image.h"
#include "Constants.h"
#include "Hitbox.h"
#include <iostream>
#include <cmath>
#include "DebugLogger.h"

class Player : public GameObject{
    public:
        Player();
        Player(GameObject* base);
        Player(SDL_Renderer* ren);
        Player(SDL_Renderer* ren, Vector2 pos);
        ~Player();

        Vector2 getSpeed();
        
        void handleEvents(SDL_Event e);
        void handleInput(const uint8_t* state);
        void update();
        void handleCollision(Hitbox* local, Hitbox* other);
        void move();
        void draw();
        void detectCollisions();
    private:
        Vector2 _speed;
        float _acceleration;  // TODO: Should no longer be a constant, use newtonian physics instead
        Vector2 _dir; // The direction the player is moving in, should be normalized
        bool _onGround;
        float _jumpSpeed;
        bool _doJump;
        Hitbox* _groundChecker; // Hitbox to check if player is touching the ground

        void setPosition(Vector2 newPos);
        const float MAX_DIR_LEN = 1.5;
        const float PLAYER_MAX_SPEED = 0.5;
        const float PLAYER_SLOWDOWN_ACC = 0.1;
        const float PLAYER_MIN_SPEED = PLAYER_MAX_SPEED / 8;
        void terrainCollision(Hitbox* local, Hitbox* terrain);
        void init();
};

#endif /* Player_h */
