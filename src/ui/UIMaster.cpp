#include "UIMaster.h"

UIMaster::UIMaster(SDL_Renderer* renderer){
    _ren = renderer;

    TTF_Init();
    std::string fontpath = ASSETS_PATH + "fonts/DejaVuSansMono.ttf"; 
    TTF_Font* standard_font = TTF_OpenFont(fontpath.c_str(), 20);
    // Init UI objects
    // Init Debugger
    // TODO: add separate debubber object?
    DebugLogger* logger = new DebugLogger(1, _ren, standard_font);
    _elements.push_back(logger);
}

UIMaster::~UIMaster(){
    for(int i = 0; i < _elements.size(); i++){
        delete _elements[i];
    }
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

UIElement* UIMaster::getElement(int index){
    return _elements[index];
}
