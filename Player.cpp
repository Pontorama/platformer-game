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
        std::cout << e.key.keysym.sym << std::endl;
        switch(e.key.keysym.sym){
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
                this->dir = {0, 0};
                break;
        }
        this->dir.normalise();
    }else{
        //this->dir = {0,0};
    }
}

void Player::update(){
    this->destRect.x += (pos.x + dir.x * speed * TIME_PER_FRAME);
    this->destRect.y += (pos.y + dir.y * speed * TIME_PER_FRAME);
    GameObject::update();
}

void Player::render(){
    GameObject::render();
}