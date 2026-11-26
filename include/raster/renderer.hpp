#pragma once

#include "./math/vec3.hpp"
#include "render_target.hpp"
#include "mesh.hpp"

void renderMesh(RenderTarget& target, const Mesh& mesh, const Mat4& model, const Mat4& view, const Mat4& projection, const Color& color, const Vec3& lightDirection);