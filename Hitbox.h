#ifndef Hitbox_h
#define Hitbox_h

#include "Vector2.h"

class Hitbox{
    public:
        Hitbox();
        Hitbox(Vector2 pos, Vector2 size);
        bool overlaps(Hitbox other);
    private:
        Vector2 _pos;
        Vector2 _size;
};

#endif 