#include <gtest/gtest.h>
#include <math/mat4.hpp>
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline double deg2rad(double degrees) {
    return degrees * M_PI / 180.0;
}   

void expectMatricesNear(const Mat4& a, const Mat4& b,float epsilon){
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            EXPECT_NEAR(a.data[r][c], b.data[r][c], epsilon);
        }
    }
}

TEST(Mat4Test, ConstructDefaultMatrix) {
    Mat4 m;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            EXPECT_FLOAT_EQ(m.data[r][c], 0.0f);
        }
    }
}

TEST(Mat4Test, ConstructMatrixWithGivenValues) {
    float values[4][4] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Mat4 m{values};

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            EXPECT_FLOAT_EQ(m.data[r][c], values[r][c]);
        }
    }
}

TEST(Mat4Test, ConstructIdentityMatrix) {
    Mat4 i = Mat4::identity();

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++){
            if(r == c) EXPECT_FLOAT_EQ(i.data[r][c], 1.0f);
            else EXPECT_FLOAT_EQ(i.data[r][c], 0.0f);
        }
    }
}

TEST(Mat4Test, MultiplicationOfMatrices) {
    float valuesA[4][4] = {
        {1, 2, 0, 0},
        {3, 4, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    float valuesB[4][4] = {
        {2, 0, 0, 0},
        {1, 3, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    float ans[4][4] = {
        {4, 6, 0, 0},
        {10, 12, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    Mat4 mA{valuesA};
    Mat4 mB{valuesB};

    Mat4 m = mA*mB;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            EXPECT_FLOAT_EQ(m.data[r][c], ans[r][c]);
        }
    }
}

TEST(Mat4Test, MultiplicationOfMatrixAndVec4) {
    float values[4][4] = {
        {1, 0, 0, 5},
        {0, 1, 0, 2},
        {0, 0, 1, -3},
        {0, 0, 0, 1}
    };

    Mat4 m{values};
    Vec4 v{1.0f, 2.0f, 3.0f, 1.0f};
    Vec4 ans{6.0f, 4.0f, 0.0f, 1.0f};

    Vec4 mv = m*v;

    EXPECT_FLOAT_EQ(mv.x, ans.x);
    EXPECT_FLOAT_EQ(mv.y, ans.y);
    EXPECT_FLOAT_EQ(mv.z, ans.z);
    EXPECT_FLOAT_EQ(mv.w, ans.w);
}

TEST(Mat4Test, TranslationDoesNotAffectDirectionVec4) {
    float values[4][4] = {
        {1, 0, 0, 5},
        {0, 1, 0, 2},
        {0, 0, 1, -3},
        {0, 0, 0, 1}
    };

    Mat4 m{values};
    Vec4 v{1.0f, 2.0f, 3.0f, 0.0f};

    Vec4 mv = m * v;

    EXPECT_FLOAT_EQ(mv.x, 1.0f);
    EXPECT_FLOAT_EQ(mv.y, 2.0f);
    EXPECT_FLOAT_EQ(mv.z, 3.0f);
    EXPECT_FLOAT_EQ(mv.w, 0.0f);
}

TEST(Mat4Test, MultiplicationByIdentityMatrix) {
    float values[4][4] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Mat4 m{values};

    Mat4 i = Mat4::identity();

    Mat4 m1 = m*i;
    Mat4 m2 = i*m;

    expectMatricesNear(m1, m, 1e-5f);
    expectMatricesNear(m2, m, 1e-5f);
}

TEST(Mat4Test,ConstructViewMatrix) {
    Vec3 e{0.0f, 0.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};

    float values[4][4] = {
        { 1, 0, 0, 0},
        { 0, 1, 0, 0},
        { 0, 0, 1, -5},
        { 0, 0, 0, 1}
    };

    Mat4 m{values};
    Mat4 vm = Mat4::lookAt(e, t, u);

    expectMatricesNear(m, vm, 1e-5f);
}

TEST(Mat4Test,CameraOriginCheck) {
    Vec3 e{0.0f, 0.0f, 5.0f};
    Vec3 t{0.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};

    Mat4 vm = Mat4::lookAt(e, t, u);
    Vec4 eyePoint{0.0f, 0.0f, 5.0f, 1.0f};

    Vec4 res = vm * eyePoint;

    EXPECT_FLOAT_EQ(res.x, 0.0f);
    EXPECT_FLOAT_EQ(res.y, 0.0f);
    EXPECT_FLOAT_EQ(res.z, 0.0f);
    EXPECT_FLOAT_EQ(res.w, 1.0f);
}

TEST(Mat4Test, RotationAfterViewMatrix) {
    Vec3 e{0.0f, 0.0f, 0.0f};
    Vec3 t{1.0f, 0.0f, 0.0f};
    Vec3 u{0.0f, 1.0f, 0.0f};

    Mat4 vm = Mat4::lookAt(e, t, u);
    Vec4 target{1.0f, 0.0f, 0.0f, 1.0f};

    Vec4 res = vm * target;

    EXPECT_FLOAT_EQ(res.x, 0.0f);
    EXPECT_FLOAT_EQ(res.y, 0.0f);
    EXPECT_FLOAT_EQ(res.z, -1.0f);
    EXPECT_FLOAT_EQ(res.w, 1.0f);
}

TEST(Mat4Test, PerspectiveMatrix) {
    float FOV = 90.0f;
    float aspect = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    float a = -11.0f /9.0f;
    float b = -20.0f /9.0f;
    
    float values[4][4] = {
        { 1, 0, 0, 0},
        { 0, 1, 0, 0},
        { 0, 0, a, b},
        { 0, 0, -1, 0}
    };
    
    Mat4 m{values};
    Mat4 ans = Mat4::perspective(deg2rad(FOV), aspect, near, far);
    
    expectMatricesNear(m, ans, 1e-5f);

    Vec4 nearPoint{0,0,-1,1};
    Vec4 farPoint{0,0,-10,1};

    Vec4 nM = ans*nearPoint;
    Vec4 fM = ans*farPoint;

    float ndcZN = nM.z / nM.w;
    float ndcZF = fM.z / fM.w;

    EXPECT_NEAR(ndcZN, -1.0f, 1e-5f);
    EXPECT_NEAR(ndcZF, 1.0f, 1e-5f);
}

TEST(Mat4Test, TransposeOfMatrix) {
    float values[4][4] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Mat4 m{values};

    Mat4 mT = m.transpose();

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            EXPECT_FLOAT_EQ(m.data[r][c], mT.data[c][r]);
        }
    }
}

TEST(Mat4Test, DoubleTransposeOfMatrix) {
    float values[4][4] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Mat4 m{values};

    Mat4 mTT = m.transpose().transpose();

    expectMatricesNear(m, mTT, 1e-5f);
}

TEST(Mat4Test, AssociativityOfMatrixMultiplication) {
    float valuesA[4][4] = {
        {1, 2, 0, 0},
        {3, 4, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    float valuesB[4][4] = {
        {2, 0, 0, 0},
        {1, 3, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    float valuesC[4][4] = {
        {1, 0, 2, 0},
        {0, 1, 0, 3},
        {4, 0, 1, 0},
        {0, 5, 0, 1}
    };

    Mat4 mA{valuesA};
    Mat4 mB{valuesB};
    Mat4 mC{valuesC};

    Mat4 left = (mA*mB)*mC;
    Mat4 right = mA*(mB*mC);

    expectMatricesNear(left, right, 1e-5f);
}