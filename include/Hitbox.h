#ifndef Hitbox_h
#define Hitbox_h

#include "Vector2.h"
#include "Constants.h"

class Hitbox{
    public:
        Hitbox();
        Hitbox(Vector2 pos, Vector2 size);
        Hitbox(Vector2 pos, Vector2 size, int mask);
        bool overlaps(Hitbox* other);
        void setPosition(Vector2 newPos);
        Vector2 getPos();
        Vector2 getPrevPos();
        void move(Vector2 v);
        Vector2 getSize();
        int getMask();
        void setMask(int newMask);
    private:
        Vector2 _pos;
        Vector2 _prevPos; // Previous position
        Vector2 _size;
        int _mask;
};

#endif 