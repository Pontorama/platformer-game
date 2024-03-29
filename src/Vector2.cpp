#include "Vector2.h"

using namespace Vector;

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
    
}

void Vector2::normalise(){
    float len = getLength();
    if(len != 0){
        x = x / len;
        y = y / len;
    }
}

Vector2 Vector2::operator+(const Vector2 &v){
    Vector2 new_v = Vector2();
    new_v.x = v.x + this->x;
    new_v.y = v.y + this->y;
    return new_v;
}

float Vector2::operator*(const Vector2 &v){
    return this->x*v.x + this->y*v.y;
}

Vector2 Vector2::operator*(float s){
    Vector2 new_v = Vector2();
    new_v.x = this->x * s;
    new_v.y = this->y * s;
    return new_v;
}

Vector2 Vector2::operator*(int s){
    Vector2 new_v = Vector2();
    new_v.x = this->x * s;
    new_v.y = this->y * s;
    return new_v;
}

Vector2 Vector2::operator*(double s){
    Vector2 new_v = Vector2();
    new_v.x = this->x * s;
    new_v.y = this->y * s;
    return new_v;
}

void Vector2::operator+=(const Vector2 &v){
    this->x+=v.x;
    this->y+=v.y;
}

std::string Vector2::toString(){
    return "X: " + std::to_string(this->x) + " Y: " + std::to_string(this->y);
}

Vector2 Vector2::operator%(const Vector2 &v){
    // Elementwise multiplication
    return Vector2(this->x * v.x, this->y * v.y);
}

/*!
    Get distance between two points, represented as vectors
*/
float Vector::getDistance(Vector2 v1, Vector2 v2){
    return sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}
