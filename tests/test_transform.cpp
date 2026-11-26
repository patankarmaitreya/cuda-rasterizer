#include <gtest/gtest.h>
#include <math/transform.hpp>
#include <math/vec4.hpp>
#include <math/mat4.hpp>
#include <math/vec3.hpp>
#include <cmath>

TEST(TransformTest, PerspectiveDivideTest){
    Vec4 clip{2.0f, 1.0f, -1.0f, 4.0f};

    Vec3 v = perspectiveDivide(clip);

    EXPECT_NEAR(v.x, 0.5f, 1e-5f);
    EXPECT_NEAR(v.y, 0.25f, 1e-5f);
    EXPECT_NEAR(v.z, -0.25f, 1e-5f);
}

TEST(TransformTest, ViewportTransformTest){
    Vec3 ndc{0.5f, -0.5f, 0.25f};

    Vec3 v = viewportTransform(ndc, 800.0f, 600.0f);

    EXPECT_NEAR(v.x, 600.0f, 1e-5f);
    EXPECT_NEAR(v.y, 450.0f, 1e-5f);
    EXPECT_NEAR(v.z, 0.25f, 1e-5f);
}

TEST(TransformTest, EntirePipelineTest){
    Vec4 worldPoint{0.0f, 0.0f, 0.0f, 1.0f};

    Vec3 e{0.0f, 0.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};
    
    float FOV = 90.0f;
    float aspect = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    float width = 800.0f; 
    float height = 600.0f;

    Mat4 view = Mat4::lookAt(e, t, u);
    Mat4 projection = Mat4::perspective(deg2rad(FOV), aspect, near, far);
    
    Vec4 camera = view * worldPoint;
    Vec4 clip = projection * camera;

    Vec3 ndc = perspectiveDivide(clip);
    Vec3 screen = viewportTransform(ndc, width, height);

    EXPECT_NEAR(screen.x, 400.0f, 1e-5f);
    EXPECT_NEAR(screen.y, 300.0f, 1e-5f);
}

TEST(TransformTest, EntirePipelineTestOffCenterPoint){
    Vec4 worldPoint{1.0f, 1.0f, 0.0f, 1.0f};

    Vec3 e{0.0f, 0.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};
    
    float FOV = 90.0f;
    float aspect = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    float width = 800.0f; 
    float height = 600.0f;

    Mat4 view = Mat4::lookAt(e, t, u);
    Mat4 projection = Mat4::perspective(deg2rad(FOV), aspect, near, far);
    
    Vec4 camera = view * worldPoint;
    Vec4 clip = projection * camera;

    Vec3 ndc = perspectiveDivide(clip);
    Vec3 screen = viewportTransform(ndc, width, height);

    EXPECT_NEAR(screen.x, 480.0f, 1e-4f);
    EXPECT_NEAR(screen.y, 240.0f, 1e-4f);
}


TEST(TransformTest, PointOutsideFrustumTest){
    Vec4 worldPoint{10.0f, 1.0f, 0.0f, 1.0f};

    Vec3 e{0.0f, 0.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};
    
    float FOV = 90.0f;
    float aspect = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    Mat4 view = Mat4::lookAt(e, t, u);
    Mat4 projection = Mat4::perspective(deg2rad(FOV), aspect, near, far);
    
    Vec4 camera = view * worldPoint;
    Vec4 clip = projection * camera;

    EXPECT_FALSE(isInsideFrustum(clip));
}



TEST(TransformTest, PointInsideFrustumTest){
    Vec4 worldPoint{0.0f, 0.0f, 0.0f, 1.0f};

    Vec3 e{0.0f, 0.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};
    
    float FOV = 90.0f;
    float aspect = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    Mat4 view = Mat4::lookAt(e, t, u);
    Mat4 projection = Mat4::perspective(deg2rad(FOV), aspect, near, far);
    
    Vec4 camera = view * worldPoint;
    Vec4 clip = projection * camera;

    EXPECT_TRUE(isInsideFrustum(clip));
}

TEST(TransformTest, TransformVertexToScreen){
    Vec3 vertex{0.0f, 0.0f, 0.0f};

    Vec3 e{0.0f, 0.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};
    
    float FOV = 90.0f;
    float aspect = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    float width = 800.0f; 
    float height = 800.0f;

    Mat4 view = Mat4::lookAt(e, t, u);
    Mat4 projection = Mat4::perspective(deg2rad(FOV), aspect, near, far);
    
    Vec3 screen = transformVertexToScreen(vertex, Mat4::identity(), view, projection, width, height);

    EXPECT_NEAR(screen.x, 400.0f, 1e-4f);
    EXPECT_NEAR(screen.y, 400.0f, 1e-4f);
    EXPECT_NEAR(screen.z, 7.0f / 9.0f, 1e-4f);
}
