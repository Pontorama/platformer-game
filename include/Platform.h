#ifndef Platform_h
#define Platform_h

#include "GameObject.h"
#include <string>

class Platform : public  GameObject{
    // A simple platform, primarily to test things
    // TODO use same pos and dimensions as texture
    public:
        Platform(GameObject* base, int id);
        Platform(SDL_Renderer* renderer, Animator* animator, vector<Hitbox*> hitboxes, Vector2 pos, string name);
        Platform(SDL_Renderer* ren, Vector2 pos);
        Platform(SDL_Renderer* ren, Vector2 pos, std::string name, int id);
        ~Platform();

        void update();
    private:
        void actOnCollision(GameObject* other);
};

#endif
