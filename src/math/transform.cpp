#include <math/transform.hpp>

Vec3 perspectiveDivide(const Vec4& clip){
    return Vec3(clip.x/clip.w, clip.y/clip.w, clip.z/clip.w);
}

Vec3 viewportTransform(const Vec3& ndc, float width, float height){
    return Vec3(((ndc.x+1.0f)/2.0f)*width, ((1.0f-ndc.y)/2.0f)*height, ndc.z);
}

bool isInsideFrustum(const Vec4& clip){
    if (clip.w <= 0.0f) {
        return false;
    }
    
    return (clip.x >= -1.0f * clip.w && clip.x <= clip.w) && 
            (clip.y >= -1.0f * clip.w && clip.y <= clip.w) && 
            (clip.z >= -1.0f * clip.w && clip.z <= clip.w);
}