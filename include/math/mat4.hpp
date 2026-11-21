#pragma once

#include "vec3.hpp"
#include "vec4.hpp"

class Mat4 {
public:
    // Row-major storage: data[row][column]
    float data[4][4];

    Mat4();
    Mat4(const float values[4][4]);

    Mat4 operator*(const Mat4& other) const;
    Vec4 operator*(const Vec4& v) const;

    static Mat4 identity();
    static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up);
    static Mat4 perspective( float fovYRadians, float aspect, float nearPlane, float farPlane);

    Mat4 transpose() const;
};