#include "Player.h"

Player::Player(){
    this->speed = 5;
}

Player::Player(const char* textureSheet, SDL_Renderer* ren) : GameObject(textureSheet, ren){
    this->speed = 0.25;
}

Player::~Player(){

}

float Player::getSpeed(){
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
    // Check for length in each direction
}

void Player::update(){
    this->destRect.x += (pos.x + dir.x * speed * TIME_PER_FRAME);
    this->destRect.y += (pos.y + dir.y * speed * TIME_PER_FRAME);
    GameObject::update();
}

void Player::render(){
    GameObject::render();
}