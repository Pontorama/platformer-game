#ifndef RenderUtils_h
#define RenderUtils_h

#include "SDL2/SDL_render.h"

namespace RenderUtils{
    struct RenderInfo {
        /*!
        * Type to hold all parameters to be passed to SDL_RenderCopy
        * Objects to-be-rendered should pass this to a camera object to be rendered
        * Use of this makes for less code and a more robust rendering pipeline
        * */
        SDL_Texture* texture;
        SDL_Rect* srcRect;
        SDL_Rect* destRect;
    };

    bool boxInsideBox(SDL_Rect box1, SDL_Rect box2);
}
#endif
