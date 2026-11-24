#include <raster/render_target.hpp>
#include <raster/rasterizer.hpp>

int main(){
    RenderTarget target{200, 200};

    Vec3 aNear{50.0f, 30.0f, 0.2f};
    Vec3 bNear{150.0f, 30.0f, 0.2f};
    Vec3 cNear{100.0f, 160.0f, 0.2f};

    Vec3 aFar{50.0f, 30.0f, 0.7f};
    Vec3 bFar{150.0f, 30.0f, 0.7f};
    Vec3 cFar{100.0f, 160.0f, 0.7f};

    Color black{0, 0, 0};
    Color red{255, 0, 0};
    Color blue{0, 0, 255};

    target.framebuffer.clear(black);
    target.depthbuffer.clear();

    rasterizeTriangle(target, aFar, bFar, cFar, blue);
    rasterizeTriangle(target, aNear, bNear, cNear, red);
    bool success1 = target.framebuffer.writePPM("triangle1.ppm");

    rasterizeTriangle(target, aNear, bNear, cNear, red);
    rasterizeTriangle(target, aFar, bFar, cFar, blue);
    bool success2 = target.framebuffer.writePPM("triangle2.ppm");

    if(success1 && success2) return 0;
    else return 1;
}