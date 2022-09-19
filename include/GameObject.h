#ifndef GameObject_h
#define GameObject_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2.h"
#include "Constants.h"
#include "TextureManager.h"
#include "RenderUtils.h"
#include <iostream>
#include <vector>
#include "Hitbox.h"
#include <tuple>
#include "Animator.h"

using namespace std;
using namespace Vector;

class GameObject{
    public:
        // Constructors
        GameObject();
        GameObject(GameObject* go, int id);
        GameObject(SDL_Renderer* ren);
        GameObject(SDL_Renderer* ren, Vector2 pos);

        //Destructor
        virtual ~GameObject();  

        // Getters
        float getXPos();
        float getYPos();
        Vector2 getPos();
        string getName();
        void setName(string newName);
        SDL_Rect* getSrcRect();
        SDL_Rect* getDestRect();
        SDL_Texture* getNextFrame();

        tuple<Hitbox*, Hitbox*> isColliding(GameObject* other);
        virtual void actOnCollision(Hitbox* local_hitbox, Hitbox* other);
        virtual void handleEvents(SDL_Event e);
        virtual void handleInput(const uint8_t* state);
        void setPosition(Vector2 newPos);

        // Hitbox getters
        int getHitboxCount();
        Hitbox* getHitbox(int index);
        vector<Hitbox*> getHitboxes();

        // Initers for animator
        void initAnimator(map<string, Sequence> sequences);
        void initAnimator(SDL_Texture* defaultTexture);

        // Update and render, collision detection
        virtual void update();
        void setNearbyHitboxes(vector<Hitbox*> hitboxes);
        void addNearbyHitboxes(vector<Hitbox*> hitboxes);
        void clearNearbyHitboxes();
        virtual void detectCollisions();

    protected:
        void _init(SDL_Renderer* ren);
        SDL_Renderer* _renderer;
        Vector2 _pos;
        Vector2 _prevPos; // Previous position
        Vector2 _imageSize;
        SDL_Rect _srcRect, _destRect;
        SDL_Renderer* _ren;
        vector<Hitbox*> _hitboxes; // Potential FIXME , might not be how to handle lists in this case
        string _name;
        int _id;
        void drawAllHitboxOutlines();
        void drawHitboxOutline(Hitbox* hb, SDL_Color c);
        vector<Hitbox*> _nearbyHitboxes;
        Animator _animator; // Optional animator
};

#endif /* GameObject_h */
