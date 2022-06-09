#include "UIMaster.h"

UIMaster::UIMaster(SDL_Renderer* renderer){
    _ren = renderer;

    // FIXME: Only for testing
    TTF_Init();
    std::string fontpath = ASSETS_PATH + "fonts/DejaVuSansMono.ttf"; 
    TextBox* test = new TextBox(1, _ren, Vector2(200, 200), Vector2(100, 100), "Test", TTF_OpenFont(fontpath.c_str(), 50), {0, 0, 0});
    _elements.push_back(test);
}

UIMaster::~UIMaster(){

}

void UIMaster::renderAllElements(){
    for(int i = 0; i < _elements.size(); i++){
        _elements[i]->render();
    }
}

void UIMaster::updateElement(int elementID, string action){

}

void UIMaster::addElement(UIElement* elementToAdd){
    _elements.push_back(elementToAdd);
}

void UIMaster::removeElement(int elementID){

}