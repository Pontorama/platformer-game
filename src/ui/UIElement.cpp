/*
    Base class for building more complex UI elements
*/

#include "UIElement.h"

UIElement::UIElement(int ID, SDL_Renderer* renderer){
    _ID = ID;
    _ren = renderer;
}

UIElement::~UIElement(){

}

void UIElement::update(){

}

void UIElement::render(){

}

int UIElement::getID(){
    return _ID;
}

Vector2 UIElement::getPos(){
    return _pos;
}

void UIElement::_init(){
    
}