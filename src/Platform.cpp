#include "Platform.h"

Platform::Platform(const char* textureSheet,SDL_Renderer* ren, Vector2 pos) : GameObject(textureSheet, ren, pos){
    Hitbox* hb = new Hitbox(_pos, _imageSize, TERRAIN_MASK);
    _hitboxes.push_back(hb); // Potential FIXME, hb might not need to be pointer?
}

Platform::~Platform(){
    
}

void Platform::render(){
    GameObject::render();
}

void Platform::update(){
    
}

void Platform::actOnCollision(GameObject* other){ 
}
