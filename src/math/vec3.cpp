#include <math/vec3.hpp>
#include <cmath>

Vec3::Vec3(float a, float b, float c) : x(a), y(b), z(c) {
}

Vec3 Vec3::operator+(const Vec3& other) const{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const{
    return Vec3(x*scalar, y*scalar, z*scalar);    
}

float Vec3::dot(const Vec3& other) const{
    return (x*other.x + y*other.y + z*other.z);
}

Vec3 Vec3::cross(const Vec3& other) const{
    return Vec3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}

float Vec3::length() const{
    return std::sqrt(dot(*this));
}

Vec3 Vec3::normalized() const{
    float len = length();

    if(len == 0.0f) return Vec3(0.0f, 0.0f, 0.0f);

    return Vec3(x/len, y/len, z/len);
}