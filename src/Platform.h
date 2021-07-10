#include "GameObject.h"

class Platform :public  GameObject{
    // A simple platform, primarily to test things
    // TODO use same pos and dimensions as texture
    public:
        Platform(const char* textureSheet, SDL_Renderer* ren, Vector2 pos);
        ~Platform();

        void render();
        void update();
};