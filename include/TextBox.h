#ifndef TextBox_h
#define TextBox_h

#include <string>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"


#include "UIElement.h"

using namespace Vector;

class TextBox : public UIElement{
    public:
        TextBox(int ID, SDL_Renderer* renderer);
        TextBox(int ID, SDL_Renderer* renderer, TTF_Font* font);
        TextBox(int ID, SDL_Renderer* renderer, Vector2 pos, Vector2 size);
        TextBox(int ID, SDL_Renderer* renderer, Vector2 pos, Vector2 size, string text);
        TextBox(int ID, SDL_Renderer* renderer, Vector2 pos, Vector2 size, string text, TTF_Font* font, SDL_Color c);
        virtual ~TextBox();

        string getText();
        void setText(string newText);

        void render();
        void update();
    protected:
        string _text;
        Vector2 _size;
        // TODO: define defaults for all of these
        TTF_Font* _font;
        SDL_Color _color;

        void _init();

};

#endif
