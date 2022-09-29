#include "Platform.h"

Platform::Platform(SDL_Renderer* renderer, Animator* animator, vector<Hitbox*> hitboxes, Vector2 pos, string name) : GameObject(renderer){
    _pos = pos;
    // Replace animator
    delete _animator;
    _animator = animator;
    // Replace hitboxes
    if(hitboxes.size() > 0){
        _hitboxes = hitboxes;
    }else{
        // Create default hitbox
        Hitbox* hb = new Hitbox(_pos, getImageSize(), TERRAIN_MASK);
        _hitboxes.push_back(hb); // Potential FIXME, hb might not need to be pointer?
    }

    _name = name;
}

Platform::Platform(SDL_Renderer* ren, Vector2 pos) : GameObject(ren, pos){
    Hitbox* hb = new Hitbox(_pos, getImageSize(), TERRAIN_MASK);
    _hitboxes.push_back(hb); // Potential FIXME, hb might not need to be pointer?
}

Platform::Platform(SDL_Renderer* ren, Vector2 pos, std::string name, int id) : GameObject(ren, pos){
    Hitbox* hb = new Hitbox(_pos, getImageSize(), TERRAIN_MASK);
    _hitboxes.push_back(hb); // Potential FIXME, hb might not need to be pointer?
    _name = name;
    _id = id;
}

Platform::Platform(GameObject* base, int id) : GameObject(base, id){
    Hitbox* hb = new Hitbox(_pos, getImageSize(), TERRAIN_MASK);
    _hitboxes.push_back(hb);
}

Platform::~Platform(){
}

void Platform::update(){
    
}

void Platform::actOnCollision(GameObject* other){ 
}
