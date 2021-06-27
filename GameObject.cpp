#include "GameObject.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren){
    this->ren = ren;
    this->objTexture = TextureManager::loadTexture(textureSheet, ren);
    this->pos = Vector2(0,0);

    this->srcRect = {0, 0, PLAYER_SIZE, PLAYER_SIZE};
    this->destRect = {0, 0, PLAYER_SIZE, PLAYER_SIZE};
}

GameObject::GameObject(){
    this->ren = NULL;
    this->objTexture = NULL;
    this->pos = Vector2();

    this->srcRect = {0, 0, 0, 0};
    this->destRect = {0, 0, 0, 0};
}

GameObject::~GameObject(){

}

void GameObject::update(){
    
}

void GameObject::render(){
    SDL_RenderCopy(this->ren, this->objTexture, &srcRect, &destRect);
}

float GameObject::getXPos(){
    return this->pos.x;
}

float GameObject::getYPos(){
    return this->pos.y;
}

Vector2 GameObject::getPos(){
    return this->pos; // Should be pointer?
}