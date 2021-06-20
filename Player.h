#ifndef Player_h
#define Player_h

#include "GameObject.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class Player : public GameObject{
    public:
        Player(std::string imagepath);
        ~Player();
        float getSpeed();
    private:
        float speed;
};

#endif /* Player_h */