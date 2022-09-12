#include "CameraUtils.h"


/*!
 * Check if all of box1 is inside box2
 * */
bool CameraUtils::boxInsideBox(SDL_Rect box1, SDL_Rect box2){
    bool xContained = false;
    bool yContained = false;

    // Check if size in x-dir is contained
    if((box1.x >= box2.x) && ((box1.x + box1.w) <= (box2.x + box2.w))){
        xContained = true;
    }

    if((box1.y >= box2.y) && ((box1.y + box1.h) <= (box2.y + box2.h))){
        yContained = true;
    }

    return xContained && yContained;
}
