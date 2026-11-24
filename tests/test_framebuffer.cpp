#include <gtest/gtest.h>
#include <optional>
#include <raster/framebuffer.hpp>

TEST(FramebufferTest, ConstructBuffer) {
    Framebuffer fb{4, 3};

    auto pixel1 = fb.getPixel(0, 0);
    ASSERT_TRUE(pixel1.has_value());

    EXPECT_EQ(pixel1->r, 0);
    EXPECT_EQ(pixel1->g, 0);
    EXPECT_EQ(pixel1->b, 0);

    auto pixel2 = fb.getPixel(3, 2);
    ASSERT_TRUE(pixel2.has_value());

    EXPECT_EQ(pixel2->r, 0);
    EXPECT_EQ(pixel2->g, 0);
    EXPECT_EQ(pixel2->b, 0);

    auto pixel3 = fb.getPixel(0, 2);
    ASSERT_TRUE(pixel3.has_value());

    EXPECT_EQ(pixel3->r, 0);
    EXPECT_EQ(pixel3->g, 0);
    EXPECT_EQ(pixel3->b, 0);
}

TEST(FramebufferTest, SetAndGetPixel) {
    Framebuffer fb{4, 3};
    Color red{255, 0, 0};

    fb.setPixel(2, 1, red);
    auto pixel = fb.getPixel(2, 1);
    ASSERT_TRUE(pixel.has_value());

    EXPECT_EQ(pixel->r, 255);
    EXPECT_EQ(pixel->g, 0);
    EXPECT_EQ(pixel->b, 0);
}

TEST(FramebufferTest, OutOfBoundsSet) {
    Framebuffer fb{4, 3};
    Color red{255, 0, 0};

    fb.setPixel(-1, 0, red);
    fb.setPixel(4, 0, red);
    fb.setPixel(0, 3, red);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 4; x++) {
            auto pixel = fb.getPixel(x, y);
    
            ASSERT_TRUE(pixel.has_value());
    
            EXPECT_EQ(pixel->r, 0);
            EXPECT_EQ(pixel->g, 0);
            EXPECT_EQ(pixel->b, 0);
        }
    }
}

TEST(FramebufferTest, OutOfBoundsGet) {
    Framebuffer fb{4, 3};
    Color red{255, 0, 0};

    EXPECT_FALSE(fb.getPixel(-1, 0).has_value());
    EXPECT_FALSE(fb.getPixel(4, 0).has_value());
    EXPECT_FALSE(fb.getPixel(0, 3).has_value());
}

TEST(FramebufferTest, ClearFrameBuffer) {
    Framebuffer fb{4, 3};
    
    Color red{255, 0, 0};
    Color green{0, 255, 0};
    
    fb.setPixel(0, 0, red);
    fb.setPixel(1, 2, red);
    fb.setPixel(3, 1, red);
    
    fb.clear(green);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 4; x++) {
            auto pixel = fb.getPixel(x, y);
    
            ASSERT_TRUE(pixel.has_value());
    
            EXPECT_EQ(pixel->r, 0);
            EXPECT_EQ(pixel->g, 255);
            EXPECT_EQ(pixel->b, 0);
        }
    }
}