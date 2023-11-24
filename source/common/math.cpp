#include <commotion/math.hpp>

#include <cmath>

using namespace Commotion;

/* ------ VECTOR2 ---------- */
Vector2::Vector2() {
    this->x = this->y = 0;
}


Vector2::Vector2(real x, real y) {
    this->x = x;
    this->y = y;
}


void Vector2::operator=(const Vector2& other) {
    this->x = other.x;
    this->y = other.y;
}


Vector2 Vector2::operator-(const Vector2& other) {
    return Vector2(this->x - other.x, this->y - other.y);
}


Vector2 Vector2::operator+(const Vector2& other) {
    return Vector2(this->x + other.x, this->y + other.y);
}


Vector2 Vector2::operator*(const Vector2& other) {
    return Vector2(this->x * other.x, this->y * other.y);
}


Vector2 Vector2::operator-(real scalar) {
    return Vector2(this->x - scalar, this->y - scalar);
}


Vector2 Vector2::operator+(real scalar) {
    return Vector2(this->x + scalar, this->y + scalar);
}


Vector2 Vector2::operator*(real scalar) {
    return Vector2(this->x * scalar, this->y * scalar);
}


Vector2 Vector2::operator/(real scalar) {
    return Vector2(this->x / scalar, this->y / scalar);
}


void Vector2::operator-=(const Vector2& other) {
    this->x -= other.x;
    this->y -= other.y;
}


void Vector2::operator+=(const Vector2& other) {
    this->x += other.x;
    this->y += other.y;
}


void Vector2::operator*=(const Vector2& other) {
    this->x *= other.x;
    this->y *= other.y;
}


void Vector2::operator-=(real scalar) {
    this->x -= scalar;
    this->y -= scalar;
}


void Vector2::operator+=(real scalar) {
    this->x += scalar;
    this->y += scalar;
}


void Vector2::operator*=(real scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

void Vector2::operator/=(real scalar) {
    this->x /= scalar;
    this->y /= scalar;
}


void Vector2::invert() {
    this->x = -x;
    this->y = -y;
}


real Vector2::square_magnitude() {
    return (this->x * this->x) + (this->y * this->y);
}


real Vector2::magnitude() {
    return sqrt(this->square_magnitude());
}


real Vector2::dot(const Vector2& other) {
    return ((this->x * other.x) + (this->y * other.y));
}


Vector2 Vector2::normalize() {
    return Vector2(this->x, this->y) / this->magnitude();
}


void Vector2::print() {
    std::cout << this->x << ", " << this->y << std::endl;
}



/* ------ VECTOR 3 ---------- */
Vector3::Vector3() {
    this->x = this->y = this->z = 0;
}


Vector3::Vector3(real x, real y, real z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


void Vector3::operator=(const Vector3& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}


Vector3 Vector3::operator-(const Vector3& other) {
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}


Vector3 Vector3::operator+(const Vector3& other) {
    return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}


Vector3 Vector3::operator*(const Vector3& other) {
    return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
}


Vector3 Vector3::operator-(real scalar) {
    return Vector3(this->x - scalar, this->y - scalar, this->z - scalar);
}


Vector3 Vector3::operator+(real scalar) {
    return Vector3(this->x + scalar, this->y + scalar, this->z + scalar);
}

Vector3 Vector3::operator*(real scalar) {
    return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}


Vector3 Vector3::operator/(real scalar) {
    return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
}


void Vector3::operator-=(const Vector3& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
}


void Vector3::operator+=(const Vector3& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}


void Vector3::operator*=(const Vector3& other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
}


void Vector3::operator-=(real scalar) {
    this->x -= scalar;
    this->y -= scalar;
    this->z -= scalar;
}


void Vector3::operator+=(real scalar) {
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;
}


void Vector3::operator*=(real scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}


void Vector3::operator/=(real scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
}


void Vector3::invert() {
    this->x = -x;
    this->y = -y;
    this->z = -z;
}


real Vector3::square_magnitude() {
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}


real Vector3::magnitude() {
    return sqrt(this->square_magnitude());
}


real Vector3::dot(const Vector3& other) {
    return ((this->x * other.x) + (this->y * other.y) + (this->z * other.z));
}


Vector3 Vector3::cross(const Vector3& other) {
    real x = (this->y * other.z) - (this->z * other.y);
    real y = (this->x * other.z) - (this->z * other.x);
    real z = (this->x * other.y) - (this->y * other.x);

    return Vector3(x, y, z);   
}


Vector3 Vector3::normalize() {
    return Vector3(this->x, this->y, this->z) / this->magnitude();
}

void Vector3::print() {
    std::cout << this->x << ", " << this->y << ", " << this->z << std::endl;
}
