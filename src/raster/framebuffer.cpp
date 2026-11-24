#include <algorithm>
#include <fstream>
#include <raster/framebuffer.hpp>

Framebuffer::Framebuffer(int width, int height) : width(width), height(height) {
    Color black{0, 0, 0};
    pixels.assign(width*height, black);
}

int Framebuffer::getWidth() const{
    return width;
}
    
int Framebuffer::getHeight() const{
    return height;
}

void Framebuffer::setPixel(int x, int y, const Color& color){
    if(x<0 || x>= width) return;
    if(y<0 || y>= height) return;

    int index = width * y + x;
    pixels[index] = color;
}

std::optional<Color> Framebuffer::getPixel(int x, int y) const{
    if(x<0 || x>= width) return std::nullopt;
    if(y<0 || y>= height) return std::nullopt;

    int index = width * y + x;
    return pixels[index];
}

void Framebuffer::clear(const Color& color){
    std::fill(pixels.begin(), pixels.end(), color);
}

bool Framebuffer::writePPM(const std::string& filename) const{
    std::ofstream file(filename, std::ios::binary);

    if (!file) return false;

    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";

    for (const Color& pixel : pixels) {
        file.put(static_cast<char>(pixel.r));
        file.put(static_cast<char>(pixel.g));
        file.put(static_cast<char>(pixel.b));
    }

    return file.good();
}