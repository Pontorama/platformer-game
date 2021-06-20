#include "GameObject.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren){
    this->objTexture = TextureManager::loadTexture(textureSheet, ren);
    this->pos = new Vector2();
}

GameObject::~GameObject(){

}

void GameObject::update(){

}

void GameObject::render(SDL_Renderer* ren){
    SDL_RenderCopy(ren, this->objTexture, NULL, NULL);
}

float GameObject::getXPos(){
    return pos->x;
}

float GameObject::getYPos(){
    return pos->y;
}

Vector2* GameObject::getPos(){
    return this->pos; // Should be pointer?
}