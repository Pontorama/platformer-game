#include "GameObject.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren){
    _ren = ren;
    _objTexture = TextureManager::loadTexture(textureSheet, ren);
    _pos = Vector2(0,0);

    _srcRect = {0, 0, PLAYER_SIZE, PLAYER_SIZE};
    _destRect = {0, 0, PLAYER_SIZE, PLAYER_SIZE};
}

GameObject::GameObject(){
    _ren = NULL;
    _objTexture = NULL;
    _pos = Vector2();

    _srcRect = {0, 0, 0, 0};
    _destRect = {0, 0, 0, 0};
}

GameObject::~GameObject(){

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