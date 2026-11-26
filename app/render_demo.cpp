#include <math/transform.hpp>
#include <raster/renderer.hpp>

int main(){
    RenderTarget target{400, 400};

    target.framebuffer.clear({0, 0, 0});
    target.depthbuffer.clear();

    Mesh cube;

    cube.vertices = {
        {-1.0f, -1.0f, -1.0f}, // 0
        { 1.0f, -1.0f, -1.0f}, // 1
        { 1.0f,  1.0f, -1.0f}, // 2
        {-1.0f,  1.0f, -1.0f}, // 3

        {-1.0f, -1.0f,  1.0f}, // 4
        { 1.0f, -1.0f,  1.0f}, // 5
        { 1.0f,  1.0f,  1.0f}, // 6
        {-1.0f,  1.0f,  1.0f}  // 7
    };

    cube.triangles = {
        // z = -1
        {0, 2, 1},
        {0, 3, 2},
    
        // z = +1
        {4, 5, 6},
        {4, 6, 7},
    
        // x = -1
        {0, 7, 3},
        {0, 4, 7},
    
        // x = +1
        {1, 6, 5},
        {1, 2, 6},
    
        // y = -1
        {0, 5, 4},
        {0, 1, 5},
    
        // y = +1
        {3, 6, 2},
        {3, 7, 6}
    };

    Vec3 e{3.0f, 3.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};

    Vec3 lightDirection{1.0f, 0.4f, 0.7f};
    
    float FOV = 90.0f;
    float aspect = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    Mat4 view = Mat4::lookAt(e, t, u);
    Mat4 projection = Mat4::perspective(deg2rad(FOV), aspect, near, far);

    renderMesh(target, cube, Mat4::identity(), view, projection, {255, 0, 0}, lightDirection);

    bool success = target.framebuffer.writePPM("reference_cube.ppm");

    if(success) return 0;
    else return 1;
}