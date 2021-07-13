#ifndef GameObject_h
#define GameObject_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2.h"
#include "Constants.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include "Hitbox.h"

class GameObject{
    public:
        // Constructors
        GameObject();
        GameObject(const char* textureSheet, SDL_Renderer* ren);
        GameObject(const char* textureSheet, SDL_Renderer* ren, Vector2 pos);

        //Destructor
        virtual ~GameObject();  

        // Getters
        float getXPos();
        float getYPos();
        Vector2 getPos();
        int getMask();

        GameObject* isColliding(GameObject* other);
        void actOnCollision(GameObject* other);
        virtual void handleEvents(SDL_Event e); // TODO this breaks player controls?

        // Update and render
        void update();
        void render();
    protected:
        void _init(const char* textureSheet, SDL_Renderer* ren);
        Vector2 _pos;
        Vector2 _imageSize;
        int _mask;
        SDL_Texture* _objTexture;
        SDL_Rect _srcRect, _destRect;
        SDL_Renderer* _ren;
        std::vector<Hitbox*> _hitboxes; // Potential FIXME , might not be how to handle lists in this case
};

#endif /* GameObject_h */