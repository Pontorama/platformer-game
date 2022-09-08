#include "Hitbox.h"

Hitbox::Hitbox(){
    _pos = {0,0};
    _prevPos = _pos;
    _size = {0,0};
}

Hitbox::Hitbox(Vector2 pos, Vector2 size){
    _pos = pos;
    _prevPos = _pos;
    _size = size;
    _mask = DEFAULT_MASK;
}

Hitbox::Hitbox(Vector2 pos, Vector2 size, int mask){
    _pos = pos;
    _prevPos = pos;
    _size = size;
    _mask = mask;
}

bool Hitbox::overlaps(Hitbox* other){
    Vector2 otherPos = other->getPos();
    Vector2 otherSize = other->getSize();

    // Check if axis overlaps one at a time
    // If overlap on both axis, collision occured
    bool xOverlap = false;
    bool yOverlap = false;

    if(otherPos.x + otherSize.x < _pos.x || otherPos.x < _pos.x + _size.x){
        xOverlap = true;
    }

    if(otherPos.y + otherSize.y > _pos.y || otherPos.y < _pos.y + _size.y){
        yOverlap = true;
    }
    return xOverlap && yOverlap;
}

void Hitbox::move(Vector2 v){
    // Adds the vector v to hitbox position
    _prevPos = _pos;
    _pos += v;
}

void Hitbox::setPosition(Vector2 newPos){
    // Teleport hitbox to new position
    _prevPos = _pos;
    _pos = newPos;
}

Vector2 Hitbox::getPos(){
    return _pos;
}

Vector2 Hitbox::getPrevPos(){
    return _prevPos;
}

Vector2 Hitbox::getSize(){
    return _size;
}

int Hitbox::getMask(){
    return _mask;
}

void Hitbox::setMask(int newMask){
    _mask = newMask;
}