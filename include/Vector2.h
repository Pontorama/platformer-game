#ifndef Vector2_h
#define Vector2_h

#include <math.h>
#include <string>

namespace Vector{

class Vector2{
    public:
        Vector2();
        Vector2(float x, float y);
        
        ~Vector2();
        
        Vector2 operator+(const Vector2 &v);
        float operator*(const Vector2 &v);
        Vector2 operator*(float s);
        Vector2 operator*(int s);
        Vector2 operator*(double s);
        void operator+=(const Vector2 &v);
        Vector2 operator%(const Vector2 &v); // Elementwise multiplication

        float x;
        float y;
        float getLength();
        Vector2 getNormalised();
        void normalise();
        std::string toString();
};

float getDistance(Vector2 v1, Vector2 v2);

}
#endif
