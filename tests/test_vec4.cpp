#include <gtest/gtest.h>
#include <math/vec4.hpp>

TEST(Vec4Test, ConstructsWithGivenComponents) {
    Vec4 v{1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
    EXPECT_FLOAT_EQ(v.w, 4.0f);
}