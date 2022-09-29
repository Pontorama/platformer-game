#include "Creature.h"

/*!
 * Constructors
 * ------------
*/

void Creature::init(){
    _speed = {0, 0};
    _acceleration = {0, 0};
    _dir = {0, 0};
    _onGround = false;
    Vector2 imageSize = getImageSize();
    _groundChecker = new Hitbox(_pos + Vector2(0, imageSize.y), Vector2(imageSize.x, 5), INVISIBLE_MASK);
    _hitboxes.push_back(_groundChecker);
}

/*!
 * Default constructor
 * */
Creature::Creature(){
    init();
}

Creature::Creature(GameObject* base, int id) : GameObject(base, id){
    init();
}

Creature::Creature(SDL_Renderer* ren) :GameObject(ren){
    init();

}

Creature::~Creature(){
}

/*!
 * ------------------
 * Collision handling
 * ------------------
 * */
/*!
 * Wrapper for handling collisions with other hitboxes
 * Not meant to handle collisions directly, but to identify the kind
 * of collision and pass it on
 * */
void Creature::handleCollision(Hitbox* local, Hitbox* other){
    switch(other->getMask()){
        case TERRAIN_MASK:
            if(!(local->getMask() == INVISIBLE_MASK)){
                terrainCollision(local, other);
            }
            break;

        default:
            break;
    }
}


/*!
 * Detect collisions with nearby hitboxes
 * Also handles checking if Creature is on ground
 * */
void Creature::detectCollisions(){
    for(int i = 0; i < _hitboxes.size(); i++){
        for(int j = 0; j < _nearbyHitboxes.size(); j++){
            if(_hitboxes[i]->overlaps(_nearbyHitboxes[j])){
               handleCollision(_hitboxes[i], _nearbyHitboxes[j]); 
            }
        } 
    }
    // Check if creature is on ground
    _onGround = false;
    for(int i = 0; i < _nearbyHitboxes.size(); i++){
        if(_nearbyHitboxes[i]->getMask() == TERRAIN_MASK){
            if(_groundChecker->overlaps(_nearbyHitboxes[i])){
                _onGround = true;
            }
        }
    }
}


/*!
 * Handle collisions with terrain.
 * */
void Creature::terrainCollision(Hitbox* local, Hitbox* terrain){
    // Calculate what side of the hitbox the player is colliding with
    // and stop the player from entering further into the box
    
    // Get positions and dimensions
    Vector2 lPos = local->getPos();
    Vector2 lSize = local->getSize();
    Vector2 lPrevPos = local->getPrevPos();

    Vector2 tPos = terrain->getPos();
    Vector2 tSize = terrain->getSize();

    float dx = 0;
    float dy = 0;

    // Use previous positions to decide wether collision happened in x-direction or y-direction
    if((lPos.x + lSize.x > tPos.x) && (lPrevPos.x +lSize.x <= tPos.x)){
        // Collision occured to the left of the terrain
        _speed.x = 0;
        dx = tPos.x - (lPos.x + lSize.x) -1;

    }else if((lPos.x < tPos.x + tSize.x) && (lPrevPos.x >= tPos.x + tSize.x)){
        // Collision occured to the right of the terrain
        _speed.x = 0;
        dx = tPos.x + tSize.x - lPos.x + 1;
    }

    if((lPos.y + lSize.y > tPos.y) && (lPrevPos.y + lSize.y <= tPos.y)){
       // Collision occured at top of terrain
       _speed.y = 0;
       dy = tPos.y - (lPos.y + lSize.y) - 1;

    }else if((lPos.y < tPos.y + tSize.y) && (lPrevPos.y >= tPos.y + tSize.y)){
        // Collision occured at bottom of terrain
        _speed.y = 0;
        dy = tPos.y + tSize.y - lPos.y + 1;
    }

    GameObject::setPosition(Vector2(_pos.x + dx, _pos.y + dy));
}

/*!
 * -------------------
 * Movement & updating
 * -------------------
 * */
Vector2 Creature::getSpeed(){
    return _speed;
}

void Creature::setSpeed(Vector2 newSpeed){
    _speed = newSpeed;
}

Vector2 Creature::getDir(){
    return _dir;
}

void Creature::setDir(Vector2 newDir){
    _dir  = newDir;
}

void Creature::update(){
    move();
    detectCollisions();
}

/*!
 * Move the Creature based on speed and acceleration
 * */
void Creature::move(){
    _speed += _acceleration % _dir * TIME_PER_FRAME; // % is elementwise multiplication
    
    if(abs(_speed.x) > MAX_SPEED){
        _speed.x = _speed.x / abs(_speed.x) * MAX_SPEED;
    }
    // Apply gravity
    if(!_onGround){
        _speed.y += GRAVITY * TIME_PER_FRAME;
    }
    // Stop if speed is too low
    if(abs(_speed.x) <= MIN_SPEED){
        _speed.x = 0;
    }
    // Move creature
    _pos += _speed * TIME_PER_FRAME;
    // Move hitboxes with creature
    for(auto &hb : _hitboxes){
        hb->move(_speed*TIME_PER_FRAME);
    }
}
