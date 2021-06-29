#include "Player.h"

Player::Player(){
    this->speed = {0,0};
    this->acceleration = 0.0005;

    pos = {0,0};
}

Player::Player(const char* textureSheet, SDL_Renderer* ren) : GameObject(textureSheet, ren){
    this->speed = {0,0};
    this->acceleration = 0.0005;

    pos = {0,0};
}

Player::~Player(){

}

Vector2 Player::getSpeed(){
    return this->speed;
}

void Player::handleEvents(SDL_Event e){
    // Handle player controls
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            // TODO add check for length in each dimension so movement does not clip
            case SDLK_w:
                // Move player up
                this->dir.y += -1;
                break;
            case SDLK_s:
                // Move player down
                this->dir.y += 1;
                break;
            case SDLK_d:
                // Move player right
                this->dir.x += 1;
                break;
            case SDLK_a:
                // Move player left
                this->dir.x += -1;
                break;
            default:
                break;
        }
    }else if(e.type == SDL_KEYUP){
        // If key is released player should stop moving
        switch(e.key.keysym.sym){
            case SDLK_w:
                this->dir.y = 0;
                break;
            case SDLK_s:
                this->dir.y = 0;
                break;
            case SDLK_d:
                this->dir.x = 0;
                break;
            case SDLK_a:
                this->dir.x = 0;
                break;
            default:
                break;
        }
    }
    // Always normalise
    this->dir.normalise();
    // Cap dir vector to avoid clipping
    if(std::abs(dir.x) > MAX_DIR_LEN){
        dir.x = dir.x / std::abs(dir.x) * MAX_DIR_LEN;
    }
    if(std::abs(dir.y) > MAX_DIR_LEN){
        dir.y = dir.y / std::abs(dir.y) * MAX_DIR_LEN;
    }
}

void Player::update(){
    // Update speed & position
    speed.x += dir.x * acceleration * TIME_PER_FRAME * TIME_PER_FRAME /2;
    speed.y += dir.y * acceleration * TIME_PER_FRAME * TIME_PER_FRAME /2;
    // TODO Limit max speed
    pos.x += speed.x * TIME_PER_FRAME;
    pos.y += speed.y * TIME_PER_FRAME;
    
    destRect.x = pos.x;
    destRect.y = pos.y;

    
    // Parent update function
    GameObject::update();
}

void Player::render(){
    GameObject::render();
}