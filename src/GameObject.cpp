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
    _hitboxes.clear();
    for(int i = 0; i < _nearbyHitboxes.size(); i++){
        delete _nearbyHitboxes[i];
    }
    _nearbyHitboxes.clear();
    // Free texture
    SDL_DestroyTexture(_objTexture);
}

void GameObject::update(){
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

void GameObject::handleInput(const uint8_t* state){

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

void GameObject::drawHitboxOutline(Hitbox* hb, SDL_Color c){
    // Set color
    SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
    // Draw lines
    Vector2 pos = hb->getPos();
    Vector2 size = hb->getSize();
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

void GameObject::drawAllHitboxOutlines(){
    // Set color to red by default
    SDL_Color red = {234, 19, 27, 255};
    // Draw lines
    for(int i = 0; i < this->getHitboxCount(); i++){
        drawHitboxOutline(_hitboxes[i], red);
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

SDL_Texture* GameObject::getTexture(){
    return _objTexture;
}

SDL_Rect* GameObject::getSrcRect(){
    return &_srcRect;
}

SDL_Rect* GameObject::getDestRect(){
    return &_destRect;
}

/*!
 * Return info about rendering the game object
 * TODO: Support for multiple textures?
 * */
RenderInfo GameObject::getRenderInfo(){
    RenderInfo out;
    out.texture = _objTexture;
    out.srcRect = &_srcRect;
    out.destRect = &_destRect;

    return out;
}
