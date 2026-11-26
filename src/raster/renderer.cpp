#include <math/transform.hpp>
#include <raster/rasterizer.hpp>
#include <raster/renderer.hpp>

void renderMesh(RenderTarget& target, const Mesh& mesh, const Mat4& model, const Mat4& view, const Mat4& projection, const Color& color, const Vec3& lightDirection){
    float width = target.framebuffer.getWidth();
    float  height = target.framebuffer.getHeight();
    
    Vec3 light = lightDirection.normalized();

    for (const Triangle& tri : mesh.triangles) {
        const Vec3& A = mesh.vertices[tri.i0];
        const Vec3& B = mesh.vertices[tri.i1];
        const Vec3& C = mesh.vertices[tri.i2];

        Vec4 worldA4 = model * Vec4{A.x, A.y, A.z, 1.0f};
        Vec4 worldB4 = model * Vec4{B.x, B.y, B.z, 1.0f};
        Vec4 worldC4 = model * Vec4{C.x, C.y, C.z, 1.0f};

        Vec3 worldA{worldA4.x, worldA4.y, worldA4.z};
        Vec3 worldB{worldB4.x, worldB4.y, worldB4.z};
        Vec3 worldC{worldC4.x, worldC4.y, worldC4.z};

        Vec3 normal = computeFaceNormal(worldA, worldB, worldC);
        float intensity = lambertIntensity(normal, light);

        Vec3 screenA = transformVertexToScreen(A, model, view, projection, width, height);
        Vec3 screenB = transformVertexToScreen(B, model, view, projection, width, height);
        Vec3 screenC = transformVertexToScreen(C, model, view, projection, width, height);

        Color shaded{
            static_cast<uint8_t>(color.r * intensity),
            static_cast<uint8_t>(color.g * intensity),
            static_cast<uint8_t>(color.b * intensity)
        };

        rasterizeTriangle(target, screenA, screenB, screenC, shaded);
    }
}