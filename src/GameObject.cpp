#include "GameObject.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren){

    _pos = Vector2(0,0);
    _init(textureSheet, ren);
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

    _hitboxes = std::vector<Hitbox*>();
}

GameObject::GameObject(){
    _ren = NULL;
    _objTexture = NULL;
    _pos = Vector2();

    _srcRect = {0, 0, 0, 0};
    _destRect = {0, 0, 0, 0};
}

GameObject::~GameObject(){
    for(int i = 0; i < _hitboxes.size(); i++){
        delete _hitboxes[i];
    }
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

GameObject* GameObject::isColliding(GameObject* other){
    for(int i = 0; i < _hitboxes.size(); i++){
        for(int j = i+1; j < other->getHitboxCount(); j++){
            if(_hitboxes[i]->overlaps(other->getHitbox(j))){
                return other;
            }
        }
    }
    return nullptr;
}

int GameObject::getMask(){
    return _mask;
}

void GameObject::actOnCollision(GameObject* other){

}

void GameObject::handleEvents(SDL_Event e){
    
}

int GameObject::getHitboxCount(){
    return _hitboxes.size();
}

Hitbox GameObject::getHitbox(int index){
    return *_hitboxes[index];
}

std::string GameObject::getName(){
    return _name;
}
