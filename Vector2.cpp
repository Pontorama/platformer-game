#include "Vector2.h"

Vector2::Vector2(){
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2::~Vector2(){

}

float Vector2::getLength(){
    return sqrt(x*x + y*y);
}

Vector2 Vector2::getNormalised(){
    float len = getLength();
    if(len != 0){
        return Vector2(x/len, y/len);
    }
    // TODO add error handling?
}

void Vector2::normalise(){
    float len = getLength();
    if(len != 0){
        x = x / len;
        y = y / len;
    }
}