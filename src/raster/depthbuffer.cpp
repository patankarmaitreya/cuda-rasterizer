#include <algorithm>
#include <limits>
#include <raster/depthbuffer.hpp>

Depthbuffer::Depthbuffer(int width, int height) : width(width), height(height){
    depths.assign(width*height, std::numeric_limits<float>::infinity());
}

std::optional<float> Depthbuffer::getDepth(int x, int y) const{
    if(x<0 || x>= width) return std::nullopt;
    if(y<0 || y>= height) return std::nullopt;

    int index = width * y + x;
    return depths[index];
}

void Depthbuffer::setDepth(int x, int y, float depth){
    if(x<0 || x>= width) return;
    if(y<0 || y>= height) return;

    int index = width * y + x;
    depths[index] = depth;
}

void Depthbuffer::clear(){
    std::fill(depths.begin(), depths.end(), std::numeric_limits<float>::infinity());
}