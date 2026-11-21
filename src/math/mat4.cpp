#include <math/mat4.hpp>
#include <cmath>

Mat4::Mat4(){
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            data[r][c] = 0.0f;
        }
    }
}

Mat4::Mat4(const float values[4][4]){
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            data[r][c] = values[r][c];
        }
    }
}

Mat4 Mat4::operator*(const Mat4& other) const{
    Mat4 m;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {            
            float ele = 0.0f;       
            
            for(int k=0; k<4; k++)
            {
                ele += data[r][k] * other.data[k][c];
            }

            m.data[r][c] = ele;
        }
    }

    return m;
}

Vec4 Mat4::operator*(const Vec4& v) const{
    return Vec4{
        data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3] * v.w,
        data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3] * v.w,
        data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3] * v.w,
        data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3] * v.w
    };
}

Mat4 Mat4::identity() {
    Mat4 m;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if(r == c) m.data[r][c] = 1.0f;
            else m.data[r][c] = 0.0f;
        }
    }

    return m;
}

Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& target, const Vec3& up){
    Vec3 fTemp = target - eye;
    Vec3 f = fTemp.normalized(); 

    Vec3 sTemp = f.cross(up);
    Vec3 s = sTemp.normalized();

    Vec3 u = s.cross(f);

    Mat4 m;

    m.data[0][0] = s.x;
    m.data[0][1] = s.y;
    m.data[0][2] = s.z;
    m.data[0][3] = (s.dot(eye)) * -1.0f;

    m.data[1][0] = u.x;
    m.data[1][1] = u.y;
    m.data[1][2] = u.z;
    m.data[1][3] = (u.dot(eye)) * -1.0f;

    m.data[2][0] = f.x * -1.0f;
    m.data[2][1] = f.y * -1.0f;
    m.data[2][2] = f.z * -1.0f;
    m.data[2][3] = (f.dot(eye));

    m.data[3][0] = 0;
    m.data[3][1] = 0;
    m.data[3][2] = 0;
    m.data[3][3] = 1;

    return m;
}

Mat4 Mat4::perspective( float fovYRadians, float aspect, float nearPlane, float farPlane){
    float yScale = 1.0f / std::tan(fovYRadians / 2.0f);
    float xScale = yScale / aspect;
    
    float A = (farPlane + nearPlane) / (nearPlane - farPlane);
    float B = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);

    Mat4 m;

    m.data[0][0] = xScale;
    m.data[0][1] = 0;
    m.data[0][2] = 0;
    m.data[0][3] = 0;

    m.data[1][0] = 0;
    m.data[1][1] = yScale;
    m.data[1][2] = 0;
    m.data[1][3] = 0;

    m.data[2][0] = 0;
    m.data[2][1] = 0;
    m.data[2][2] = A;
    m.data[2][3] = B;

    m.data[3][0] = 0;
    m.data[3][1] = 0;
    m.data[3][2] = -1;
    m.data[3][3] = 0;

    return m;
}

Mat4 Mat4::transpose() const{
    Mat4 m;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {            
            m.data[r][c] = data[c][r];
        }
    }

    return m;
}