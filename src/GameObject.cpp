#include "GameObject.h"

using namespace std;

GameObject::GameObject(){
    _pos = Vector2(0, 0);

}

/*!
 * Copy constructor
 * */
GameObject::GameObject(GameObject* go, int id){
    _pos = go->getPos();
    _dir = go->getDir();
    _animator = new Animator(go->_animator);
    _id = id;
    _name = go->getName();
    _hitboxes = go->getHitboxes();
    _nearbyHitboxes = go->getNearbyHitboxes();
}


GameObject::GameObject(SDL_Renderer* ren){
    _pos = Vector2(0,0);
    _init(ren);
}

GameObject::GameObject(SDL_Renderer* ren, Vector2 pos){
    _pos = pos;
    _init(ren);
}

void GameObject::_init(SDL_Renderer* ren){
    // Helper function for constructors
    // Assign _pos BEFORE calling this function
    int w, h = 32; // Default vals
    _animator = new Animator();
    _hitboxes = vector<Hitbox*>();
    _dir = {1, 0};
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
    delete _animator;
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
    return _pos; 
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


SDL_Rect GameObject::getSrcRect(){
    return _animator->getSrcRect();
}

/*!
 * Wrapper for animator getDestRect
 * */
SDL_Rect GameObject::getDestRect(){
    SDL_Rect animSrcRect = _animator->getSrcRect();

    return {(int)_pos.x, (int)_pos.y, animSrcRect.w, animSrcRect.h};
}
/*!
 * Get the frame (image) to be rendered
 * wrapper for animator, which controls what to draw on screen
 * */
SDL_Texture* GameObject::getNextFrame(){
    return _animator->getNextFrame();
}

void GameObject::setName(string newName){
    _name = newName;
}

Vector2 GameObject::getImageSize(){
    SDL_Rect animSrcRect = _animator->getSrcRect();
    return Vector2(animSrcRect.w, animSrcRect.h);
}

/*!
 * Get nearby hitboxes, which are set in game loop
 * */
vector<Hitbox*> GameObject::getNearbyHitboxes(){
    return _nearbyHitboxes;
}

/*!
 * Get current direction
 * */
Vector2 GameObject::getDir(){
    return _dir;
}

/*!
 * Set a new animator. This function makes sure the old animator gets freed
 * @param[in] newAnimator The new animator. Should be created with "new" keyword
 * */
void GameObject::setAnimator(Animator* newAnimator){
    // Make sure old animator gets freed
    delete _animator;
    // Set new animator
    _animator = newAnimator;
}

/*!
 * Get numerical ID of game object
 * */
int GameObject::getID(){
    return _id;
}
