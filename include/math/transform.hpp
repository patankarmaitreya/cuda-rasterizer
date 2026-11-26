#pragma once

#include "mat4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline double deg2rad(double degrees) {
    return degrees * M_PI / 180.0;
}  

Vec3 perspectiveDivide(const Vec4& clip);

Vec3 viewportTransform(const Vec3& ndc, float width, float height);

bool isInsideFrustum(const Vec4& clip);

Vec3 transformVertexToScreen(const Vec3& vertex, const Mat4& model, const Mat4& view, const Mat4& projection, float width, float height);