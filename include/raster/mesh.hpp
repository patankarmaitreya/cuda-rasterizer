#pragma once

#include "./math/vec3.hpp"

struct Triangle {
    int i0;
    int i1;
    int i2;
};

struct Mesh {
    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;
};