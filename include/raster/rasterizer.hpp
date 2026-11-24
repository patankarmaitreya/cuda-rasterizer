#pragma once

#include <math/vec3.hpp>
#include <raster/render_target.hpp>

float edgeFunction(const Vec3& a, const Vec3& b, const Vec3& p);

bool pointInTriangle(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& p);

Vec3 barycentricCoordinates(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& p);

void rasterizeTriangle(RenderTarget& target, const Vec3& a, const Vec3& b, const Vec3& c, const Color& color);