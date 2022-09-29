#include "Player.h"

using namespace std;

Player::Player(){
    init();
}

Player::Player(SDL_Renderer* renderer, Animator* animator, vector<Hitbox*> hitboxes, Vector2 pos, string name) : Creature(renderer){
    init();
    _pos = pos;
    // Replace animator
    delete _animator;
    _animator = animator;
    if(hitboxes.size() > 0){
        _hitboxes = hitboxes;
    }else{
        // autosize hitbox
        Hitbox* hb = new Hitbox(_pos, getImageSize(), PLAYER_MASK);
        _hitboxes.push_back(hb);
    }

    _name = name;
}

void Player::init(){
    // Initialize variables
    _speed = {0, 0};
    _pos = {0, 0};
    _acceleration = {0.005, 0.005};
    _jumpSpeed = 2.5;
    _doJump = false;
    _onGround = false;

    // Initialize hitboxes
    Hitbox* hb = new Hitbox(_pos, getImageSize(), PLAYER_MASK);
    _hitboxes.push_back(hb);
}

Player::Player(SDL_Renderer* ren) :Creature(ren){
    init();
}

Player::Player(SDL_Renderer* ren, Vector2 position) :Creature(ren){
    init();
    _pos = position;
}

/*!
 * Create Player from gameobject
 * */
Player::Player(GameObject* base, int id) : Creature(base, id){
    init();
}

Player::~Player(){
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
}

/*!
    Move the player
    Handles running and jumping
*/
void Player::move(){
    bool accelerating = std::abs(_dir.x) > 0;

    // If moving (accelerating) que walk animation
    _animator->selectSequence("Walk");

    _speed += _dir % _acceleration * TIME_PER_FRAME; // % is elementwise multiplication

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

