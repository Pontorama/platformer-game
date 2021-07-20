#ifndef Vector2_h
#define Vector2_h

#include <math.h>

class Vector2{
    public:
        Vector2();
        Vector2(float x, float y);
        
        ~Vector2();
        
        Vector2 operator+(const Vector2 &v);
        float operator*(const Vector2 &v);
        Vector2 operator*(float s);
        void operator+=(const Vector2 &v);

        float x;
        float y;
        float getLength();
        Vector2 getNormalised();
        void normalise();
};

#endif