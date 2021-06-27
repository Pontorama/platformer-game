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
    return Vector2(this->x/getLength(), this->y/getLength());
}

void Vector2::normalise(){
    this->x = x / getLength();
    this->y = y / getLength();
}