#ifndef Vector2_h
#define Vector2_h

#include <math.h>

class Vector2{
    public:
        Vector2();
        Vector2(float x, float y);
        
        ~Vector2();
        
        float x;
        float y;
        float getLength();
        Vector2* getNormalised();
};

#endif