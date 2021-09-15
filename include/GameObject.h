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
        std::string getName();

        GameObject* isColliding(GameObject* other);
        virtual void actOnCollision(GameObject* other);
        virtual void handleEvents(SDL_Event e); // TODO this breaks player controls?

        // Hitbox getters
        int getHitboxCount();
        Hitbox getHitbox(int index);

        // Update and render
        virtual void update();
        virtual void render();
    protected:
        void _init(const char* textureSheet, SDL_Renderer* ren);
        Vector2 _pos;
        Vector2 _imageSize;
        int _mask;
        SDL_Texture* _objTexture;
        SDL_Rect _srcRect, _destRect;
        SDL_Renderer* _ren;
        std::vector<Hitbox*> _hitboxes; // Potential FIXME , might not be how to handle lists in this case
        std::string _name;
};

#endif /* GameObject_h */