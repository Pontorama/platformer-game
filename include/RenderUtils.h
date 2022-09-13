#ifndef RenderUtils_h
#define RenderUtils_h

#include "SDL2/SDL_render.h"
#include "Vector2.h"

using namespace Vector;

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

    void drawOutline(SDL_Rect rect, SDL_Color c, SDL_Renderer* renderer);
    void drawOutline(Vector2 pos, Vector2 size, SDL_Color c, SDL_Renderer* renderer);
    void drawCross(Vector2 point, int size, SDL_Color c, SDL_Renderer* renderer);
}
#endif
