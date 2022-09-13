#ifndef Platform_h
#define Platform_h

#include "GameObject.h"
#include <string>

class Platform : public  GameObject{
    // A simple platform, primarily to test things
    // TODO use same pos and dimensions as texture
    public:
        Platform(const char* textureSheet, SDL_Renderer* ren, Vector2 pos);
        Platform(const char* textureSheet, SDL_Renderer* ren, Vector2 pos, std::string name, int id);
        ~Platform();

        void update();
    private:
        void actOnCollision(GameObject* other);
};

#endif
