#ifndef Creature_h
#define Creature_h

#include "GameObject.h"

using namespace std;

class Creature : public GameObject {
    public:
        Creature();
        Creature(GameObject* base, int id);
        Creature(SDL_Renderer* ren);
        ~Creature();

        Vector2 getSpeed();
        void setSpeed(Vector2 newSpeed);
        Vector2 getDir();
        void setDir(Vector2 newDir);
        
        void update();
        void move();

    protected:
        Vector2 _speed;
        Vector2 _acceleration;
        bool _onGround;
        Hitbox* _groundChecker;

        void detectCollisions();
        void terrainCollision(Hitbox* local, Hitbox* terrain);
        void handleCollision(Hitbox* local, Hitbox* other);

        const float MAX_SPEED = 0.5; // Default value
        const float MIN_SPEED = MAX_SPEED / 8; // Default value

        void init();
};

#endif
