#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

enum KeyPresses{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_TOTAL
};


void testArrows(SDL_Event e){
        switch(e.key.keysym.sym){
            case SDLK_UP:
                printf("Up\n");
                break;
            
            case SDLK_DOWN:
                printf("Down\n");
                break;

            case SDLK_LEFT:
                printf("Left\n");
                break;
            
            case SDLK_RIGHT:
                printf("Right\n");
                break;
        }
    return;
}