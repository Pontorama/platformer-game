#include "Hitbox.h"

Hitbox::Hitbox(){
    _pos = {0,0};
    _size = {0,0};
}

Hitbox::Hitbox(Vector2 pos, Vector2 size){
    _pos = pos;
    _size = size;
}

bool Hitbox::overlaps(Hitbox other){
    return !( (other._pos.y > _pos.y+_size.y) && (other._pos.x > _pos.x+_size.x) && (other._pos.x + other._size.x < _pos.x) && (other._pos.y + other._size.y < _pos.y) );
}