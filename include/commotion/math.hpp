#ifndef MATH_HPP
#define MATH_HPP


#include <iostream>
#include <cassert>

#include "precision.hpp"


namespace Commotion {
    
class Vector2 {
public:
    real x;
    real y;

    Vector2();
    Vector2(real x, real y);
    
    Vector2 operator-(const Vector2& other);
    Vector2 operator+(const Vector2& other);
    Vector2 operator*(const Vector2& other);
    Vector2 operator-(real scalar);
    Vector2 operator+(real scalar);
    Vector2 operator*(real scalar);
    Vector2 operator/(real scalar);

    void operator+=(const Vector2& other);
    void operator-=(const Vector2& other);
    void operator*=(const Vector2& other); 
    void operator+=(real scalar);
    void operator-=(real scalar);
    void operator*=(real scalar);
    void operator/=(real scalar);

    void invert();
    real square_magnitude();
    real magnitude();
    real dot(const Vector2& other);
    Vector2 normalize();

    void print();
};

    
class Vector3 {
public:
    real x;
    real y;
    real z;

    Vector3();
    Vector3(real x, real y, real z);

    Vector3 operator-(const Vector3& other);
    Vector3 operator+(const Vector3& other);
    Vector3 operator*(const Vector3& other);
    Vector3 operator-(real scalar);
    Vector3 operator+(real scalar);
    Vector3 operator*(real scalar);
    
    void operator-=(const Vector3& other);
    void operator+=(const Vector3& other);
    void operator*=(const Vector3& other); 
    void operator-=(real scalar);
    void operator+=(real scalar);
    void operator*=(real scalar);

    void invert();
    real square_magnitude();
    real magnitude();
    real dot(const Vector3& other);
    Vector3 normalize();
    Vector3 cross(const Vector3& other);
    
    void print();
private:
    Vector3 operator/(real scalar);
    void operator/=(real scalar);
};

}


#endif // MATH_HPP
