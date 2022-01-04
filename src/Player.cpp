#include "Player.h"

using namespace std;

Player::Player(){
    _speed = {0,0};
    _acceleration = 0.0005;
    _pos = {0,0};
}

Player::Player(const char* textureSheet, SDL_Renderer* ren) : GameObject(textureSheet, ren){
    _speed = {0,0};
    _acceleration = 0.0005;


    _pos = {0,0};

    Hitbox* hb = new Hitbox(_pos, _imageSize, PLAYER_MASK);
    _hitboxes.push_back(hb);
}

Player::~Player(){

}

Vector2 Player::getSpeed(){
    return _speed;
}

void Player::handleEvents(SDL_Event e){
    // Handle player controls
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            // TODO add check for length in each dimension so movement does not clip
            case SDLK_w:
                // Move player up
                _dir.y += -1;
                break;
            case SDLK_s:
                // Move player down
                _dir.y += 1;
                break;
            case SDLK_d:
                // Move player right
                _dir.x += 1;
                break;
            case SDLK_a:
                // Move player left
                _dir.x += -1;
                break;
            default:
                break;
        }
    }else if(e.type == SDL_KEYUP){
        // If key is released player should stop moving
        switch(e.key.keysym.sym){
            case SDLK_w:
                _dir.y = 0;
                break;
            case SDLK_s:
                _dir.y = 0;
                break;
            case SDLK_d:
                _dir.x = 0;
                break;
            case SDLK_a:
                _dir.x = 0;
                break;
            default:
                break;
        }
    }
    // Always normalise
    _dir.normalise();
    // Cap dir vector to avoid clipping
    if(std::abs(_dir.x) > MAX_DIR_LEN){
        _dir.x = _dir.x / std::abs(_dir.x) * MAX_DIR_LEN;
    }
    if(std::abs(_dir.y) > MAX_DIR_LEN){
        _dir.y = _dir.y / std::abs(_dir.y) * MAX_DIR_LEN;
    }
}

void Player::update(){
    move();
    // Parent update function
    GameObject::update();
    
}

void Player::move(){
    bool accelerating = std::abs(_dir.x) > 0;

    // Update speed & position
    Vector2 dSpeed = _dir * _acceleration * TIME_PER_FRAME; 

    _speed += _dir * _acceleration * TIME_PER_FRAME;
    if(_speed.getLength() > PLAYER_MAX_SPEED){
        _speed = _speed * (PLAYER_MAX_SPEED / _speed.getLength());
    }

    if(!accelerating) // Only deccelerate if not accelerating
        _speed += _speed * (-1*_speed.getLength()*_speed.getLength() * PLAYER_SLOWDOWN_ACC * TIME_PER_FRAME);


    // Stop player completely if speed is low enough
    if(std::abs(_speed.x) <= PLAYER_MIN_SPEED && !accelerating)
        _speed.x = 0;

    // Update player position
    _pos += _speed * TIME_PER_FRAME;

    // Move hitboxes with player
    for(int i = 0; i < _hitboxes.size(); i++){
        _hitboxes[i]->move(_speed * TIME_PER_FRAME);
    }

    _destRect.x = _pos.x;
    _destRect.y = _pos.y;
}

void Player::render(){
    GameObject::render();
}

void Player::actOnCollision(Hitbox* local_hitbox, Hitbox* other){
    // This function should be called upon collision with another hitbox
    // other is a pointer to the object the player colliding with
    if(other->getMask() == TERRAIN_MASK){
        // Colliding with terrain
        terrainCollision(local_hitbox, other);
    }
}

void Player::terrainCollision(Hitbox* local, Hitbox* terrain){
    // TODO implement relative position in case of movin terrain

    // Calculate what side of the hitbox the player is colliding with
    // and stop the player from entering further into the box
    
    // Get positions and dimensions
    Vector2 lPos = local->getPos();
    Vector2 lSize = local->getSize();
    Vector2 lPrevPos = local->getPrevPos();

    Vector2 tPos = terrain->getPos();
    Vector2 tSize = terrain->getSize();

    // Use previous positions to decide wether collision happened in x-direction or y-direction
    if((lPos.x + lSize.x > tPos.x) && (lPrevPos.x +lSize.x <= tPos.x)){
        // Collision occured to the left of the terrain
        _speed.x = 0;
        float dx = tPos.x - (lPos.x + lSize.x);
        GameObject::setPosition(Vector2(_pos.x + dx, _pos.y));

    }else if((lPos.x < tPos.x + tSize.x) && (lPrevPos.x >= tPos.x + tSize.x)){
        // Collision occured to the right of the terrain
        _speed.x = 0;
        float dx = tPos.x + tSize.x - lPos.x;
        GameObject::setPosition(Vector2(_pos.x + dx, _pos.y));
    }

    if((lPos.y + lSize.y > tPos.y) && (lPrevPos.y + lSize.y <= tPos.y)){
       // Collision occured at top of terrain
       _speed.y = 0;
       float dy = tPos.y - (lPos.y + lSize.y);
       GameObject::setPosition(Vector2(_pos.x, _pos.y + dy));

    }else if((lPos.y < tPos.y + tSize.y) && (lPrevPos.y >= tPos.y + tSize.y)){
        // Collision occured at bottom of terrain
        _speed.y = 0;
        float dy = tPos.y + tSize.y - lPos.y;
        GameObject::setPosition(Vector2(_pos.x, _pos.y + dy));
    }
    
}