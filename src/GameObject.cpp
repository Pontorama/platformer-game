#include "GameObject.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren){

    _pos = Vector2(0,0);
    _init(textureSheet, ren);
    _hitboxes = new std::vector<Hitbox*>;
}

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, Vector2 pos){
    _pos = pos;
    _init(textureSheet, ren);
}

void GameObject::_init(const char* textureSheet, SDL_Renderer* ren){
    // Helper function for constructors
    // Assign _pos BEFORE calling this function
    _ren = ren;
    _objTexture = TextureManager::loadTexture(textureSheet, ren);
    int w, h;

    SDL_QueryTexture(_objTexture, NULL, NULL, &w, &h);
    _imageSize = {w,h};
    _imageSize.x *= SCALE_FACTOR_X;
    _imageSize.y *= SCALE_FACTOR_Y;
    _srcRect = {0, 0, w, h};
    _destRect = {(int)_pos.x, (int)_pos.y, (int)_imageSize.x, (int)_imageSize.y};
}

GameObject::GameObject(){
    _ren = NULL;
    _objTexture = NULL;
    _pos = Vector2();

    _srcRect = {0, 0, 0, 0};
    _destRect = {0, 0, 0, 0};
}

GameObject::~GameObject(){
    delete _hitboxes;
}

void GameObject::update(){
    
}

void GameObject::render(){
    SDL_RenderCopy(_ren, _objTexture, &_srcRect, &_destRect);
}

float GameObject::getXPos(){
    return _pos.x;
}

float GameObject::getYPos(){
    return _pos.y;
}

Vector2 GameObject::getPos(){
    return _pos; // Should be pointer?
}