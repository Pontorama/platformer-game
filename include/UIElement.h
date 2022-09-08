#ifndef UIElement_h
#define UIElement_h

#include <string>

#include "Vector2.h"
#include "SDL2/SDL_render.h"

using namespace std;
using namespace Vector;

class UIElement{
    // Container for UI elements (text/images/etc)
    public:
        UIElement(int ID, SDL_Renderer* renderer);
        virtual ~UIElement();

        int getID();
        Vector2 getPos();

        virtual void render();
        virtual void update();

    protected:
        // Functions
        virtual void _init();
        // Variables
        int _ID;
        Vector2 _pos; // Absolute position on screen
        SDL_Renderer* _ren;

};

#endif
