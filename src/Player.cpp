#include "Player.h"

using namespace std;

Player::Player(){
    init();
}

void Player::init(){
    // Initialize variables
    _speed = {0, 0};
    _acceleration = 0.0005;
    _pos = {0, 0};
    _jumpSpeed = 2.5;
    _doJump = false;
    _onGround = false;

    // Initialize hitboxes
    Hitbox* hb = new Hitbox(_pos, _imageSize, PLAYER_MASK);
    _hitboxes.push_back(hb);
    // Add hitbox to check if player is touching the ground or not
    _groundChecker = new Hitbox(_pos + Vector2(0, _imageSize.y), Vector2(_imageSize.x, 5), INVISIBLE_MASK);
    _hitboxes.push_back(_groundChecker);
}

Player::Player(const char* textureSheet, SDL_Renderer* ren) : GameObject(textureSheet, ren){
    init();
}

Player::Player(const char* textureSheet, SDL_Renderer* ren, Vector2 position) : GameObject(textureSheet, ren){
    init();
    _pos = position;
}

Player::~Player(){
    // Run destructor for parent class
    GameObject::~GameObject();
}

Vector2 Player::getSpeed(){
    return _speed;
}

void Player::handleInput(const uint8_t* state){
    _dir = {0, 0};
    if(state[SDL_SCANCODE_D]){
        _dir.x += 1;
    }
    if(state[SDL_SCANCODE_A]){
        _dir.x -= 1;
    }
    if(state[SDL_SCANCODE_S]){
        _dir.y -= 1;
    }
    if(state[SDL_SCANCODE_W]){
        _dir.y += 1;
    }
    if(state[SDL_SCANCODE_SPACE]){
        _doJump = true;
    }

    _dir.normalise();
}

void Player::handleEvents(SDL_Event e){

} 

void Player::update(){
    move();
    detectCollisions();
    draw();
    // Parent update function
    GameObject::update();
}

/*!
    Move the player
    Handles running and jumping
*/
void Player::move(){
    bool accelerating = std::abs(_dir.x) > 0;

    _speed += _dir * _acceleration * TIME_PER_FRAME;

    if(std::abs(_speed.x) > PLAYER_MAX_SPEED){
        _speed.x = _speed.x * (PLAYER_MAX_SPEED / std::abs(_speed.x));
    }

    if(!accelerating) // Only deccelerate if not accelerating
        _speed.x += _speed.x * (-1*_speed.x*_speed.x * PLAYER_SLOWDOWN_ACC * TIME_PER_FRAME);

    // gravity
    if(!_onGround){
        _speed.y += GRAVITY * TIME_PER_FRAME;
    }

    // jumping
    if(_doJump && _onGround){
        _speed.y -= _jumpSpeed;
    }

    // Stop player completely if speed is low enough
    if(std::abs(_speed.x) <= PLAYER_MIN_SPEED && !accelerating)
        _speed.x = 0;

    // Update player position
    _pos += _speed * TIME_PER_FRAME;

    // Move hitboxes with player
    for(int i = 0; i < _hitboxes.size(); i++){
        _hitboxes[i]->move(_speed * TIME_PER_FRAME);
    }

    // Reset jump
    _doJump = false;
}

/*!
    Handle collisions with terrain layer
*/
void Player::terrainCollision(Hitbox* local, Hitbox* terrain){
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

/* !
 * Check nearby hitboxes (passed from Game) for overlap
 * If overlap, pass hitbox to collision handling
 * */
void Player::detectCollisions(){
    for(int i = 0; i < _hitboxes.size(); i++){
        for(int j = 0; j < _nearbyHitboxes.size(); j++){
            if(_hitboxes[i]->overlaps(_nearbyHitboxes[j])){
               handleCollision(_hitboxes[i], _nearbyHitboxes[j]); 
            }
        } 
    }
    // Check if player is on ground
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
 * Wrapper for collision handling,
 * Act on collisions based on layer
 * */
void Player::handleCollision(Hitbox* local, Hitbox* other){
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

void Player::draw(){
    _destRect.x = _pos.x;
    _destRect.y = _pos.y;
}

