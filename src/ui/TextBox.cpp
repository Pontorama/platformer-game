#include "TextBox.h"

using namespace Vector;

TextBox::TextBox(int ID, SDL_Renderer* renderer) : UIElement(ID, renderer){
    _init();
}

TextBox::TextBox(int ID, SDL_Renderer* renderer, TTF_Font* font) : UIElement(ID, renderer){
    _font = font;
    _init();
}

TextBox::TextBox(int ID, SDL_Renderer* renderer, Vector2 pos, Vector2 size) : UIElement(ID, renderer){
    _pos = pos;
    _size = size;
    _init();
}

TextBox::TextBox(int ID, SDL_Renderer* renderer, Vector2 pos, Vector2 size, string text) : UIElement(ID, renderer){
    _pos = pos;
    _size = size;
    _text = text;
    _init();
}

TextBox::TextBox(int ID, SDL_Renderer* renderer, Vector2 pos, Vector2 size, string text, TTF_Font* font, SDL_Color c) : UIElement(ID, renderer){
    _pos = pos;
    _size = size;
    _text = text;
    _font = font;
    _color = c;

    _init();
}


TextBox::~TextBox(){

}

string TextBox::getText(){
    return _text;
}

void TextBox::setText(string newText){
    _text = newText;
}

void TextBox::_init(){
    
}

void TextBox::render(){
    SDL_Surface* surf = TTF_RenderText_Solid(_font, _text.c_str(), _color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_ren, surf);

    SDL_Rect bbox; // Bounding box
    bbox.x = _pos.x;
    bbox.y = _pos.y;
    bbox.w = _size.x;
    bbox.h = _size.y;

    SDL_RenderCopy(_ren, texture, NULL, &bbox);
    // Free memory
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}

void TextBox::update(){

}
