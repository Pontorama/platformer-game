#include "Hitbox.h"

Hitbox::Hitbox(){
    _pos = {0,0};
    _size = {0,0};
}

Hitbox::Hitbox(Vector2 pos, Vector2 size){
    _pos = pos;
    _size = size;
}

bool Hitbox::overlaps(Hitbox* other){
    Vector2 otherPos = other->getPos();
    Vector2 otherSize = other->getSize();
    return !( (otherPos.y > _pos.y+_size.y) && (otherPos.x > _pos.x+_size.x) && (otherPos.x + otherSize.x < _pos.x) && (otherPos.y + otherSize.y < _pos.y) );
}

Vector2 Hitbox::getPos(){
    return _pos;
}

Vector2 Hitbox::getSize(){
    return _size;
}