#ifndef CameraUtils_h
#define CameraUtils_h

#include "SDL2/SDL.h"

namespace CameraUtils{
    const SDL_Color FOCUS_ZONE_DEBUG_COLOR = {17, 125, 46, 255};
    const SDL_Color HITBOX_DEBUG_COLOR = {234, 19, 27, 255};
    bool boxInsideBox(SDL_Rect box1, SDL_Rect box2);
};

#endif
