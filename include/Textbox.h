#ifndef Textbox_h
#define Textbox_h

#include "GameObject.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class Textbox : public GameObject {
    public:
        Textbox();
        ~Textbox();

        void setText();
        void getText();

        void setFont();

        void render();
        void update();
    private:
        std::string text;
};

#endif