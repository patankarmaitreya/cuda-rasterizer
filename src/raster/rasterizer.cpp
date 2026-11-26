#include <raster/rasterizer.hpp>
#include <algorithm>

float edgeFunction(const Vec3& a, const Vec3& b, const Vec3& p){
    return ((p.x - a.x)*(b.y - a.y)
            - (p.y - a.y)*(b.x - a.x));
}

bool pointInTriangle(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& p){
    float ab = edgeFunction(a, b, p);
    float bc = edgeFunction(b, c, p);
    float ca = edgeFunction(c, a, p);
    
    return (ab >= 0 && bc >= 0 && ca>= 0)
            || (ab <= 0 && bc <= 0 && ca <= 0);
}

Vec3 barycentricCoordinates(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& p){
    float area = edgeFunction(a, b, c);

    return Vec3{edgeFunction(b, c, p) / area,
                edgeFunction(c, a, p) / area, 
                edgeFunction(a, b, p) / area};
}

Vec3 computeFaceNormal(const Vec3& a, const Vec3& b,const Vec3& c){
    Vec3 edge1 = b - a;
    Vec3 edge2 = c - a;

    return edge1.cross(edge2).normalized();
}

float lambertIntensity(const Vec3& normal, const Vec3& lightDirection){
    float intensity = normal.dot(lightDirection);
    return std::max(0.0f, intensity);
}

void rasterizeTriangle(RenderTarget& target, const Vec3& a, const Vec3& b, const Vec3& c, const Color& color){
    float area = edgeFunction(a, b, c);

    if (area == 0.0f) {
        return;
    }
    
    for (int y = 0; y < target.framebuffer.getHeight(); y++) {
        for (int x = 0; x < target.framebuffer.getWidth(); x++) {
            Vec3 p{static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f, 0.0f};
            
            if (!pointInTriangle(a, b, c, p)) continue;

            Vec3 bary = barycentricCoordinates(a, b, c, p); 
            float depth = bary.x*a.z + bary.y*b.z + bary.z*c.z;

            auto storedDepth = target.depthbuffer.getDepth(x, y);

            if (depth < *storedDepth) {
                target.depthbuffer.setDepth(x, y, depth);
                target.framebuffer.setPixel(x, y, color);
            }
        }
    }
}