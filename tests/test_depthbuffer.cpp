#include <gtest/gtest.h>
#include <optional>
#include <cmath>

#include <raster/depthbuffer.hpp>
TEST(DepthbufferTest, ValidNewBuffer) {
    Depthbuffer db{4, 3};

    auto depth1 = db.getDepth(0, 0);
    ASSERT_TRUE(depth1.has_value());
    EXPECT_TRUE(std::isinf(*depth1));

    auto depth2 = db.getDepth(3, 2);
    ASSERT_TRUE(depth2.has_value());
    EXPECT_TRUE(std::isinf(*depth2));

    auto depth3 = db.getDepth(0, 2);
    ASSERT_TRUE(depth3.has_value());
    EXPECT_TRUE(std::isinf(*depth3));
}

TEST(DepthbufferTest, SetAndGetDepth) {
    Depthbuffer db{4, 3};

    db.setDepth(2, 1, 0.7f);

    auto depth = db.getDepth(2, 1);
    ASSERT_TRUE(depth.has_value());

    EXPECT_FLOAT_EQ(*depth, 0.7f);
}


TEST(DepthbufferTest, OutOfBoundsSet) {
    Depthbuffer db{4, 3};

    db.setDepth(-1, 0, 0.7f);
    db.setDepth(4, 0, 0.7f);
    db.setDepth(0, 3, 0.7f);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 4; x++) {
            auto depth = db.getDepth(x, y);
            ASSERT_TRUE(depth.has_value());
            
            EXPECT_TRUE(std::isinf(*depth));
        }
    }
}

TEST(DepthbufferTest, OutOfBoundsGet) {
    Depthbuffer db{4, 3};

    EXPECT_FALSE(db.getDepth(-1, 0).has_value());
    EXPECT_FALSE(db.getDepth(4, 0).has_value());
    EXPECT_FALSE(db.getDepth(0, 3).has_value());
}

TEST(DepthbufferTest, ClearDepthBuffer) {
    Depthbuffer db{4, 3};
    
    db.setDepth(0, 0, 0.7f);
    db.setDepth(1, 2, 0.7f);
    db.setDepth(3, 1, 0.7f);
    
    db.clear();

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 4; x++) {
            auto depth = db.getDepth(x, y);
            ASSERT_TRUE(depth.has_value());
        
            EXPECT_TRUE(std::isinf(*depth));
        }
    }
}