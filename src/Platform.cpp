#include "Platform.h"

Platform::Platform(SDL_Renderer* ren, Vector2 pos) : GameObject(ren, pos){
    Hitbox* hb = new Hitbox(_pos, _imageSize, TERRAIN_MASK);
    _hitboxes.push_back(hb); // Potential FIXME, hb might not need to be pointer?
}

Platform::Platform(SDL_Renderer* ren, Vector2 pos, std::string name, int id) : GameObject(ren, pos){
    Hitbox* hb = new Hitbox(_pos, _imageSize, TERRAIN_MASK);
    _hitboxes.push_back(hb); // Potential FIXME, hb might not need to be pointer?
    _name = name;
    _id = id;
}

Platform::Platform(GameObject* base, int id) : GameObject(base, id){
    Hitbox* hb = new Hitbox(_pos, _imageSize, TERRAIN_MASK);
    _hitboxes.push_back(hb);
}

Platform::~Platform(){
    // Run parent class destructor
    GameObject::~GameObject();
}

void Platform::update(){
    
}

void Platform::actOnCollision(GameObject* other){ 
}
