#include <gtest/gtest.h>
#include <raster/rasterizer.hpp>

TEST(RasterizerTest, EdgeFunctionTest) {
    Vec3 A{1.0f, 1.0f, 0.0f};
    Vec3 B{5.0f, 1.0f, 0.0f};
    Vec3 C{3.0f, 4.0f, 0.0f};

    Vec3 p{3.0f, 2.0f, 0.0f};

    EXPECT_FLOAT_EQ(edgeFunction(A, B, p), -4.0f);
    EXPECT_FLOAT_EQ(edgeFunction(B, C, p), -4.0f);
    EXPECT_FLOAT_EQ(edgeFunction(C, A, p), -4.0f);
}

TEST(RasterizerTest, PointInsideTriangle) {
    Vec3 A{1.0f, 1.0f, 0.0f};
    Vec3 B{5.0f, 1.0f, 0.0f};
    Vec3 C{3.0f, 4.0f, 0.0f};

    Vec3 p{3.0f, 2.0f, 0.0f};

    EXPECT_TRUE(pointInTriangle(A, B, C, p));    
}

TEST(RasterizerTest, PointOutsideTriangle) {
    Vec3 A{1.0f, 1.0f, 0.0f};
    Vec3 B{5.0f, 1.0f, 0.0f};
    Vec3 C{3.0f, 4.0f, 0.0f};

    Vec3 p{6.0f, 2.0f, 0.0f};
    
    EXPECT_FALSE(pointInTriangle(A, B, C, p));    
}

TEST(RasterizerTest, PointOnTriangle) {
    Vec3 A{1.0f, 1.0f, 0.0f};
    Vec3 B{5.0f, 1.0f, 0.0f};
    Vec3 C{3.0f, 4.0f, 0.0f};

    Vec3 p{3.0f, 1.0f, 0.0f};

    EXPECT_TRUE(pointInTriangle(A, B, C, p));
}

TEST(RasterizerTest, BarycentricCoordinatesTest) {
    Vec3 A{1.0f, 1.0f, 0.0f};
    Vec3 B{5.0f, 1.0f, 0.0f};
    Vec3 C{3.0f, 4.0f, 0.0f};

    Vec3 barycentricA = barycentricCoordinates(A, B, C, A);
    Vec3 barycentricB = barycentricCoordinates(A, B, C, B);
    Vec3 barycentricC = barycentricCoordinates(A, B, C, C);

    EXPECT_NEAR(barycentricA.x, 1.0f, 1e-5f);
    EXPECT_NEAR(barycentricA.y, 0.0f, 1e-5f);
    EXPECT_NEAR(barycentricA.z, 0.0f, 1e-5f);

    EXPECT_NEAR(barycentricB.x, 0.0f, 1e-5f);
    EXPECT_NEAR(barycentricB.y, 1.0f, 1e-5f);
    EXPECT_NEAR(barycentricB.z, 0.0f, 1e-5f);

    EXPECT_NEAR(barycentricC.x, 0.0f, 1e-5f);
    EXPECT_NEAR(barycentricC.y, 0.0f, 1e-5f);
    EXPECT_NEAR(barycentricC.z, 1.0f, 1e-5f);
}

TEST(RasterizerTest, BarycentricCoordinatesSumTest){
    Vec3 A{1.0f, 1.0f, 0.0f};
    Vec3 B{5.0f, 1.0f, 0.0f};
    Vec3 C{3.0f, 4.0f, 0.0f};
    
    Vec3 p{3.0f, 2.0f, 0.0f};
    Vec3 bary = barycentricCoordinates(A, B, C, p);

    EXPECT_NEAR(bary.x + bary.y + bary.z, 1.0f, 1e-5f);
}

TEST(RasterizerTest, FarFirstDrawOrder){
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

    auto pixel = target.framebuffer.getPixel(100, 80);
    ASSERT_TRUE(pixel.has_value());

    EXPECT_EQ(pixel->r, 255);
    EXPECT_EQ(pixel->g, 0);
    EXPECT_EQ(pixel->b, 0);
}

TEST(RasterizerTest, NearFirstDrawOrder){
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

    rasterizeTriangle(target, aNear, bNear, cNear, red);
    rasterizeTriangle(target, aFar, bFar, cFar, blue);

    auto pixel = target.framebuffer.getPixel(100, 80);
    ASSERT_TRUE(pixel.has_value());

    EXPECT_EQ(pixel->r, 255);
    EXPECT_EQ(pixel->g, 0);
    EXPECT_EQ(pixel->b, 0);
}


TEST(RasterizerTest, RenderComprisionForDiffernetDrawOrder){
    RenderTarget target1{200, 200};
    RenderTarget target2{200, 200};

    Vec3 aNear{50.0f, 30.0f, 0.2f};
    Vec3 bNear{150.0f, 30.0f, 0.2f};
    Vec3 cNear{100.0f, 160.0f, 0.2f};
    
    Vec3 aFar{50.0f, 30.0f, 0.7f};
    Vec3 bFar{150.0f, 30.0f, 0.7f};
    Vec3 cFar{100.0f, 160.0f, 0.7f};

    Color black{0, 0, 0};
    Color red{255, 0, 0};
    Color blue{0, 0, 255};

    target1.framebuffer.clear(black);
    target1.depthbuffer.clear();

    target2.framebuffer.clear(black);
    target2.depthbuffer.clear();

    rasterizeTriangle(target1, aFar, bFar, cFar, blue);
    rasterizeTriangle(target1, aNear, bNear, cNear, red);

    rasterizeTriangle(target2, aNear, bNear, cNear, red);    
    rasterizeTriangle(target2, aFar, bFar, cFar, blue);

    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 200; x++) {
            auto p1 = target1.framebuffer.getPixel(x, y);
            auto p2 = target2.framebuffer.getPixel(x, y);
    
            ASSERT_TRUE(p1.has_value());
            ASSERT_TRUE(p2.has_value());
    
            EXPECT_EQ(p1->r, p2->r);
            EXPECT_EQ(p1->g, p2->g);
            EXPECT_EQ(p1->b, p2->b);
        }
    }
}

TEST(RasterizerTest, DegenerateTriangleDoesNotRender){
    RenderTarget target{200, 200};

    Vec3 A{10.0f, 10.0f, 0.2f};
    Vec3 B{20.0f, 20.0f, 0.2f};
    Vec3 C{30.0f, 30.0f, 0.2f};

    Color black{0, 0, 0};
    Color red{255, 0, 0};

    target.framebuffer.clear(black);
    target.depthbuffer.clear();

    rasterizeTriangle(target, A, B, C, red);

    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 200; x++) {
            auto pixel = target.framebuffer.getPixel(x, y);
    
            ASSERT_TRUE(pixel.has_value());
    
            EXPECT_EQ(pixel->r, 0);
            EXPECT_EQ(pixel->g, 0);
            EXPECT_EQ(pixel->b, 0);
        }
    }
}