#pragma once

#include "vec3.hpp"
#include "vec4.hpp"

Vec3 perspectiveDivide(const Vec4& clip);

Vec3 viewportTransform(const Vec3& ndc, float width, float height);

bool isInsideFrustum(const Vec4& clip);