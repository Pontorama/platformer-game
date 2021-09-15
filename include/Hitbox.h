#ifndef Hitbox_h
#define Hitbox_h

#include "Vector2.h"

class Hitbox{
    public:
        Hitbox();
        Hitbox(Vector2 pos, Vector2 size);
        bool overlaps(Hitbox other);
        Vector2 getPos();
        void move(Vector2 v);
        Vector2 getSize();
    private:
        Vector2 _pos;
        Vector2 _size;
};

#endif 