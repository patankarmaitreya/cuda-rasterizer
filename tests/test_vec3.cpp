#include <gtest/gtest.h>
#include <math/vec3.hpp>

TEST(Vec3Test, ConstructsWithGivenComponents) {
    Vec3 v{1.0f, 2.0f, 3.0f};

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vec3Test, AddingTwoVectors) {
    Vec3 a{1.0f, 2.0f, 3.0f};
    Vec3 b{4.0f, -1.0f, 2.0f};

    Vec3 v = a + b;

    EXPECT_FLOAT_EQ(v.x, 5.0f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
    EXPECT_FLOAT_EQ(v.z, 5.0f);
}

TEST(Vec3Test, SubtractingTwoVectors) {
    Vec3 a{7.0f, 3.0f, 1.0f};
    Vec3 b{2.0f, -1.0f, 4.0f};

    Vec3 v = a - b;

    EXPECT_FLOAT_EQ(v.x, 5.0f);
    EXPECT_FLOAT_EQ(v.y, 4.0f);
    EXPECT_FLOAT_EQ(v.z, -3.0f);
}

TEST(Vec3Test, ScalarMultiplicationOfVectors) {
    Vec3 a{1.0f, -2.0f, 3.0f};

    Vec3 v = a * 2.0f;

    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, -4.0f);
    EXPECT_FLOAT_EQ(v.z, 6.0f);
}

TEST(Vec3Test, DotProductOfVectors) {
    Vec3 a{1.0f, 2.0f, 3.0f};
    Vec3 b{4.0f, -1.0f, 2.0f};

    float v = a.dot(b);

    EXPECT_FLOAT_EQ(v, 8.0f);
}

TEST(Vec3Test, DotProductOfPerpendicularVectors) {
    Vec3 a{1.0f, 0.0f, 0.0f};
    Vec3 b{0.0f, 0.0f, 1.0f};

    float v = a.dot(b);

    EXPECT_FLOAT_EQ(v, 0.0f);
}

TEST(Vec3Test, CrossProductOfVectors) {
    Vec3 a{1.0f, 0.0f, 0.0f};
    Vec3 b{0.0f, 1.0f, 0.0f};

    Vec3 v = a.cross(b);

    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 1.0f);  
}

TEST(Vec3Test, CrossProductIsPerpendicularToInputs) {
    Vec3 a{1.0f, 2.0f, 3.0f};
    Vec3 b{4.0f, 5.0f, 6.0f};

    Vec3 v = a.cross(b);

    EXPECT_NEAR(v.dot(a), 0.0f, 1e-5f);
    EXPECT_NEAR(v.dot(b), 0.0f, 1e-5f);
}

TEST(Vec3Test, LengthOfVectors) {
    Vec3 a{3.0f, 4.0f, 0.0f};

    float v = a.length();

    EXPECT_NEAR(v, 5.0f, 1e-5f);
}

TEST(Vec3Test, NormalizeVectors) {
    Vec3 a{0.0f, 3.0f, 4.0f};

    Vec3 v = a.normalized();

    EXPECT_NEAR(v.x, 0.0f, 1e-5f);
    EXPECT_NEAR(v.y, 0.6f, 1e-5f);
    EXPECT_NEAR(v.z, 0.8f, 1e-5f);

    EXPECT_NEAR(v.length(), 1.0f, 1e-5f);
}

TEST(Vec3Test, NormalizeZeroVectors) {
    Vec3 a{0.0f, 0.0f, 0.0f};

    Vec3 v = a.normalized();

    EXPECT_NEAR(v.x, 0.0f, 1e-5f);
    EXPECT_NEAR(v.y, 0.0f, 1e-5f);
    EXPECT_NEAR(v.z, 0.0f, 1e-5f);
}