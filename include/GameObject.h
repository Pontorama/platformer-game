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
#include <tuple>

using namespace std;
using namespace Vector;

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
        string getName();

        tuple<Hitbox*, Hitbox*> isColliding(GameObject* other);
        virtual void actOnCollision(Hitbox* local_hitbox, Hitbox* other);
        virtual void handleEvents(SDL_Event e);
        void setPosition(Vector2 newPos);

        // Hitbox getters
        int getHitboxCount();
        Hitbox* getHitbox(int index);
        vector<Hitbox*> getHitboxes();

        // Update and render, collision detection
        virtual void update();
        virtual void render();
        void setNearbyHitboxes(vector<Hitbox*> hitboxes);
        void addNearbyHitboxes(vector<Hitbox*> hitboxes);
        void clearNearbyHitboxes();
        virtual void detectCollisions();

    protected:
        void _init(const char* textureSheet, SDL_Renderer* ren);
        SDL_Renderer* _renderer;
        Vector2 _pos;
        Vector2 _prevPos; // Previous position
        Vector2 _imageSize;
        SDL_Texture* _objTexture;
        SDL_Rect _srcRect, _destRect;
        SDL_Renderer* _ren;
        vector<Hitbox*> _hitboxes; // Potential FIXME , might not be how to handle lists in this case
        string _name;
        int _id;
        void drawHitboxOutlines();
        vector<Hitbox*> _nearbyHitboxes;
};

#endif /* GameObject_h */
