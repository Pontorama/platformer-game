#include "Player.h"

Player::Player(){
    _speed = {0,0};
    _acceleration = 0.0005;

    _pos = {0,0};
}

Player::Player(const char* textureSheet, SDL_Renderer* ren) : GameObject(textureSheet, ren){
    _speed = {0,0};
    _acceleration = 0.0005;

    _pos = {0,0};
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
    bool accelerating = std::abs(_dir.x) > 0;

    // Update speed & position
    _speed += _dir * _acceleration * TIME_PER_FRAME;
    if(_speed.getLength() > PLAYER_MAX_SPEED){
        _speed = _speed * (PLAYER_MAX_SPEED / _speed.getLength());
    }

    // TODO implement gravity
    if(!accelerating) // Only deccelerate if not accelerating
        _speed += _speed * (-1*_speed.getLength()*_speed.getLength() * PLAYER_SLOWDOWN_ACC * TIME_PER_FRAME);


    // Stop player completely if speed is low enough
    if(std::abs(_speed.x) <= PLAYER_MIN_SPEED && !accelerating)
        _speed.x = 0;

    // Update player position
    _pos.x += _speed.x * TIME_PER_FRAME;
    _pos.y += _speed.y * TIME_PER_FRAME;
    
    _destRect.x = _pos.x;
    _destRect.y = _pos.y;

    
    // Parent update function
    GameObject::update();
}

void Player::render(){
    GameObject::render();
}