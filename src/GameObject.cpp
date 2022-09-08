#include "GameObject.h"

using namespace std;

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren){
    _pos = Vector2(0,0);
    _init(textureSheet, ren);
    _renderer = ren;
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
    _imageSize = {(float)w, (float)h};
    _imageSize.x *= SCALE_FACTOR_X;
    _imageSize.y *= SCALE_FACTOR_Y;
    _srcRect = {0, 0, w, h};
    _destRect = {(int)_pos.x, (int)_pos.y, (int)_imageSize.x, (int)_imageSize.y};

    _hitboxes = vector<Hitbox*>();
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
    if(DEBUG_MODE){
        drawHitboxOutlines();
    }
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

tuple<Hitbox*, Hitbox*> GameObject::isColliding(GameObject* other){
    // Returns overlapping hitboxes as a tuple
    // <Other, This>
    tuple<Hitbox*, Hitbox*> out;
    for(int i = 0; i < _hitboxes.size(); i++){
        for(int j = 0; j < other->getHitboxCount(); j++){
            if(_hitboxes[i]->overlaps(other->getHitbox(j))){
                out = make_tuple(other->getHitbox(j), _hitboxes[i]);
                return out;
            }
        }
    }
    return make_tuple(nullptr, nullptr);
}

void GameObject::actOnCollision(Hitbox* local_hitbox, Hitbox* other){
    // Local hitbox is the hitbox belonging to this gameobject, other is hitbox belonging to other gameobject
}

void GameObject::handleEvents(SDL_Event e){
    
}

int GameObject::getHitboxCount(){
    return _hitboxes.size();
}

Hitbox* GameObject::getHitbox(int index){
    return _hitboxes[index];
}

string GameObject::getName(){
    return _name;
}

void GameObject::drawHitboxOutlines(){
    // Set color to red
    SDL_SetRenderDrawColor(_renderer, 234, 19, 27, 255);
    // Draw lines
    for(int i = 0; i < this->getHitboxCount(); i++){
        Vector2 pos = _hitboxes[i]->getPos();
        Vector2 size = _hitboxes[i]->getSize();
        // Draw X-lines
        for(int u = (int)pos.x; u < (int)(pos.x + size.x); u++){
            SDL_RenderDrawPoint(_renderer, u, (int)pos.y);
            SDL_RenderDrawPoint(_renderer, u, (int)(pos.y + size.y));
        }
        // Draw Y-lines
        for(int v = (int)pos.y; v < (int)(pos.y + size.y); v++){
            SDL_RenderDrawPoint(_renderer, (int)pos.x, v);
            SDL_RenderDrawPoint(_renderer, (int)(pos.x + size.x), v);
        }
    }
}

void GameObject::setPosition(Vector2 newPos){
    // Teleport the gameobject to a new position
    
    // Calculate the offset of all hitboxes in relation to the gameobject position
    // And teleport the hitboxes keeping the offset
    for(int i = 0; i < _hitboxes.size(); i++){
        Vector2 offset = _hitboxes[i]->getPos() + _pos * -1;
        _hitboxes[i]->setPosition(newPos + offset);
    }
    
    _pos = newPos;

}

/*!
    Set the list of nearby hitboxes to be checked for collisions with
*/
void GameObject::setNearbyHitboxes(vector<Hitbox*> hitboxes){
    _nearbyHitboxes.clear();
    // Copy list
    for(int i = 0; i < hitboxes.size(); i++){
        _nearbyHitboxes.push_back(hitboxes[i]);
    }
}

void GameObject::addNearbyHitboxes(vector<Hitbox*> hitboxes){
    for(int i = 0; i < hitboxes.size(); i++){
        _nearbyHitboxes.push_back(hitboxes[i]);
    }
}

void GameObject::clearNearbyHitboxes(){
    _nearbyHitboxes.clear();
}

vector<Hitbox*> GameObject::getHitboxes(){
    vector<Hitbox*> out = _hitboxes;
    return out;
}

/*!
 * Virtual function. Wrapper for collision detection.
 * */
void GameObject::detectCollisions(){

}
